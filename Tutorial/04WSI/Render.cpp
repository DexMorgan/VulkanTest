#include "Render.h"
#include "common.h"
#include "Logger.h"

Render::Render()
{
	instance = VK_NULL_HANDLE;
	device = VK_NULL_HANDLE;
	gpu = VK_NULL_HANDLE;
	
	graphic_family_index = (uint32_t) -1;
	present_family_index = (uint32_t) -1;
}

Render::~Render()
{
}

void Render::AddInstanceLayer(const char *name)
{
	instance_layers.push_back(name);
}

void Render::AddInstanceExtension(const char *name)
{
	instance_extensions.push_back(name);
}

void Render::AddDeviceLayer(const char *name)
{
	device_layers.push_back(name);
}

void Render::AddDeviceExtension(const char *name)
{
	device_extensions.push_back(name);
}

#define VPCCI std::vector<const char *>::iterator

bool Render::RemoveInstanceLayer(const char *name)
{
	for (VPCCI i = instance_layers.begin(); i != instance_layers.end(); i++)
	{
		if (strcmp(*i, name) == 0)
		{
			instance_layers.erase(i);
			return true;
		}
	}
	return false;
}

bool Render::RemoveInstanceExtension(const char *name)
{
	for (VPCCI i = instance_extensions.begin(); i != instance_extensions.end(); i++)
	{
		if (strcmp(*i, name) == 0)
		{
			instance_extensions.erase(i);
			return true;
		}
	}
	return false;
}

bool Render::RemoveDeviceLayer(const char *name)
{
	for (VPCCI i = device_layers.begin(); i != device_layers.end(); i++)
	{
		if (strcmp(*i, name) == 0)
		{
			device_layers.erase(i);
			return true;
		}
	}
	return false;
}

bool Render::RemoveDeviceExtension(const char *name)
{
	for (VPCCI i = device_extensions.begin(); i != device_extensions.end(); i++)
	{
		if (strcmp(*i, name) == 0)
		{
			device_extensions.erase(i);
			return true;
		}
	}
	return false;
}

bool Render::CheckInstanceLayer(const char *name)
{
	uint32_t available_instance_layer_count = 0;
	if (vkEnumerateInstanceLayerProperties(&available_instance_layer_count, VK_NULL_HANDLE) != VK_SUCCESS)
		return false;
	std::vector<VkLayerProperties> available_instance_layers(available_instance_layer_count);
	if (vkEnumerateInstanceLayerProperties(&available_instance_layer_count, available_instance_layers.data()) != VK_SUCCESS)
		return false;
	for (size_t i = 0; i < available_instance_layers.size(); i++)
	{
		if (strcmp(available_instance_layers[i].layerName, name) == 0)
			return true;
	}
	return false;
}

bool Render::CheckInstanceExtension(const char *layer_name, const char *name)
{
	uint32_t available_instance_extension_count = 0;
	if (vkEnumerateInstanceExtensionProperties
		(layer_name, &available_instance_extension_count, VK_NULL_HANDLE) != VK_SUCCESS)
		return false;
	std::vector<VkExtensionProperties> available_instance_extensions(available_instance_extension_count);
	if (vkEnumerateInstanceExtensionProperties
		(layer_name, &available_instance_extension_count, available_instance_extensions.data()) != VK_SUCCESS)
		return false;
	for (size_t i = 0; i < available_instance_extensions.size(); i++)
	{
		if (strcmp(available_instance_extensions[i].extensionName, name) == 0)
			return true;
	}
	return false;
}

bool Render::CheckDeviceLayer(const char *name)
{
	uint32_t available_device_layer_count = 0;
	if (vkEnumerateDeviceLayerProperties(gpu, &available_device_layer_count, VK_NULL_HANDLE) != VK_SUCCESS)
		return false;
	std::vector<VkLayerProperties> available_device_layers(available_device_layer_count);
	if (vkEnumerateDeviceLayerProperties(gpu, &available_device_layer_count, available_device_layers.data()) != VK_SUCCESS)
		return false;
	for (size_t i = 0; i < available_device_layers.size(); i++)
	{
		if (strcmp(available_device_layers[i].layerName, name) == 0)
			return true;
	}
	return false;
}

bool Render::CheckDeviceExtension(const char *layer_name, const char *name)
{
	uint32_t available_device_extension_count = 0;
	if (vkEnumerateDeviceExtensionProperties
		(gpu, layer_name, &available_device_extension_count, VK_NULL_HANDLE) != VK_SUCCESS)
		return false;
	std::vector<VkExtensionProperties> available_device_extensions(available_device_extension_count);
	if (vkEnumerateDeviceExtensionProperties
		(gpu, layer_name, &available_device_extension_count, available_device_extensions.data()) != VK_SUCCESS)
		return false;
	for (size_t i = 0; i < available_device_extensions.size(); i++)
	{
		if (strcmp(available_device_extensions[i].extensionName, name) == 0)
			return true;
	}
	return false;
}

const VkInstance Render::GetInstance() const
{
	return instance;
}

const VkDevice Render::GetDevice() const
{
	return device;
}

void Render::EnableDebug(bool enable)
{
	if (enable)
		AddInstanceExtension(Logger::GetRequiredExtension());
	else
		RemoveInstanceExtension(Logger::GetRequiredExtension());
}

bool Render::EnableSurface(bool enable)
{
	/* И так, плоскость — это то, куда мы будем в последствии помещать изображение, если изображение должно
	 * помещаться в окно. В противном случае нам понадобиться другое расширение, которое отображает всё на экран,
	 * но к сожалению, на данный момент (1.0.8 и ниже) под Windows оно не доступно.
	 * Кстати, проверить о доступных возможностях можно через приложение vulkaninfo.
	 * Если некоторые функции, которые используют WSI, вернули VK_ERROR_SURFACE_LOST_KHR, то нам нужно уничтожить плоскость,
	 * и вместе с этим и цепочки переключений (swapchain), которую эту плоскость используют,
	 * так как они больше не пригодны к использованию.
	 * Если функции вернули VK_ERROR_OUT_OF_DATE_KHR, то это означает, что сама плосколсть не пропала, но изменилась, и нужно
	 * пересоздать цепочку переключений с новыми параметрами.
	 * 
	 * Для начала, давайте добавим неободимые расширения. Первым делом, добавим общее (базовое) расширение для плоскостей.
	 * Для этого у нас есть специальное макроимя.
	*/ 
	AddInstanceExtension(VK_KHR_SURFACE_EXTENSION_NAME);
	/* Затем, нужно добавить расширение плоскости, специальное для каждой платформы.
	 * Но перед этим нам нужно настроить заголовки Vulkan под нашу платформу, поэтому в Render.h, перед тем, как добавить
	 * vulkan.h, добавлен заголовок platform.h, который настраивает макроимена. Иначе нам просто не будут доступны необходимые
	 * функции и структуры.
	*/ 
	#if defined(VK_USE_PLATFORM_WIN32_KHR)
	AddInstanceExtension(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	#endif
	return true;
}

bool Render::CreateInstance(std::string app_name)
{
	VkApplicationInfo app_info; 
	ZM(app_info);
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = app_name.c_str();
	app_info.apiVersion = VK_MAKE_VERSION(1, 0, 8);
	app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	
	VkInstanceCreateInfo instance_info;
	ZM(instance_info);
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pApplicationInfo = &app_info;
	
	instance_info.enabledLayerCount = instance_layers.size();
	instance_info.ppEnabledLayerNames = instance_layers.data();
	
	instance_info.enabledExtensionCount = instance_extensions.size();
	instance_info.ppEnabledExtensionNames = instance_extensions.data();
	
	if (vkCreateInstance(&instance_info, NULL, &instance) != VK_SUCCESS)
		return false;
	return true;
}

bool Render::FindGPU()
{
	//Поиск GPU
	std::vector<VkPhysicalDevice> gpu_list;
	uint32_t gpu_count;
	if (vkEnumeratePhysicalDevices(instance, &gpu_count, VK_NULL_HANDLE) != VK_SUCCESS)
	{
		return false;
	}
	gpu_list.resize(gpu_count);
	if (vkEnumeratePhysicalDevices(instance, &gpu_count, gpu_list.data()) != VK_SUCCESS)
	{
		return false;
	}
	gpu = gpu_list[0];
	return true;
}

bool Render::CreateDevice()
{
	uint32_t family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_count, VK_NULL_HANDLE);
	std::vector<VkQueueFamilyProperties> family_properties_list(family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_count, family_properties_list.data());
	uint32_t valid_family_index = (uint32_t) -1;
	for (uint32_t i = 0; i < family_count; i++)
	{
		VkQueueFamilyProperties &properties = family_properties_list[i];
		if (properties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			if (valid_family_index == (uint32_t) -1)
				valid_family_index = i;
		}
	}
	if (valid_family_index == (uint32_t) -1)
	{
		return false;
	}
	
	//Индекс нам понадобится для получения очередей.
	graphic_family_index = valid_family_index;
	
	//Настройка очередей
	VkDeviceQueueCreateInfo device_queue_info;
	ZM(device_queue_info);
	device_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	float device_queue_priority[] = {1.0f};
	device_queue_info.queueCount = 1; 
	device_queue_info.queueFamilyIndex = valid_family_index; 
	device_queue_info.pQueuePriorities = device_queue_priority;
	
	//Настройка девайса
	VkDeviceCreateInfo device_info; 
    ZM(device_info);
	device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO; 
	device_info.queueCreateInfoCount = 1;
	device_info.pQueueCreateInfos = &device_queue_info;
	device_info.enabledLayerCount = device_layers.size();
	device_info.ppEnabledLayerNames = device_layers.data();
	device_info.enabledExtensionCount = device_extensions.size();
	device_info.ppEnabledExtensionNames = device_extensions.data();
	
	//Создание девайса
	if (vkCreateDevice(gpu, &device_info, NULL, &device) != VK_SUCCESS)
	{
		return false;
	}
	return true;
}

void Render::DestroyInstance()
{
	vkDestroyInstance(instance, NULL);
}

void Render::DestroyDevice()
{
	vkDestroyDevice(device, NULL);
}

const VkQueue Render::GetQueue(uint32_t index) const
{
	VkQueue queue;
	vkGetDeviceQueue(device, graphic_family_index, 0, &queue);
	return queue;
}

VkCommandPool Render::CreateCommandPool(bool reset, bool transient)
{
	VkCommandPoolCreateInfo pool_create_info;
	ZM(pool_create_info);
	pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_create_info.queueFamilyIndex = graphic_family_index;
	pool_create_info.flags = 
		(reset ? VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT : 0) |
		(transient ? VK_COMMAND_POOL_CREATE_TRANSIENT_BIT : 0);
	VkCommandPool pool = VK_NULL_HANDLE;
	vkCreateCommandPool(device, &pool_create_info, NULL, &pool);
	return pool;
}

void Render::DestroyCommandPool(VkCommandPool pool)
{
	vkDestroyCommandPool(device, pool, NULL);
}