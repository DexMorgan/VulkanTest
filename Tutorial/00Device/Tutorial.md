#������: ����������� ����������.
� ���, ��� ������ ��������� � ������������ ���������. ����� ��������� SDK � ��� ����� 3 �����, ������� ���� ����� ���������� ��� ������ ������������ ������ � ���������.
* ����� Include � � ��� ����� ����� ������������ ������.
* ����� Bin � � ��� ����� ����� ��������� (x86_64, �.�. ��� 64 ������ ����������).
* ����� Bin32 � � ��� ����� ����� ��������� (x86, �.�. ��� 32 ������ ����������).

����� �����, ����� ���������� ���� ����������: vulkan-1. �������, ��� Android ���������� ����� ����� ����������� ��� ���������� �����������, �� ��� ���� ��������� ����� � ������ ���������� ��� ����������.

�����, � ����������, ��� ����� �������������� Vulkan, ����� ���������� ������������ ���� *vulkan.h*:

	#include <vulkan/vulkan.h>

��, ������ ����� ���������� � ������.

#�������� ���������� Vulkan. ������ � ��������� �������.
��� ��� ���������� �����, �� ������ �������, ������� �� ����� ������������, ����� ���� �������� � ���������� ����������� ��������. ������� ���� ������� `vkGetInstanceProcAddr`, ������� ����� �������� � ������ �������, ��������� ��������-��������� ������� (��������, `GetProcAddress` ��� *Win32 API*). ���� �������� ����� �������� ��� ��������� �������, ���������� � ����������� � ��� ����.
**���������** (*Instance*) ����� �������� �� ������� `vkCreateInstance`, �� ������, ��� �� ����� � ������������, ����� ��������� ���������� � ���, ����� ������ ���� ��� ���������. � � Vulkan ��� �������� ������ ������� ����� ��������� ����������� ���������.
������ �����, �� ����� ������� ���������� � ����� ����������. ��� ��� �������� ��� ���������:

	typedef struct VkApplicationInfo {
		VkStructureType sType;
		const void* pNext;
		const char* pApplicationName;
		uint32_t applicationVersion;
		const char* pEngineName;
		uint32_t engineVersion;
		uint32_t apiVersion;
	} VkApplicationInfo;
	
� ������ ��������� ������ ���� ��� �����: `sType`, � ����� `pNext`. ��� ��� �� �������:
+ `sType` � ��� ���������. � ����� ������ �� ������ ������� ��� `VK_STRUCTURE_TYPE_APPLICATION_INFO`, ��� �� ������ Vulkan, ����� ������ � ��� ��������� � ����� ���������. ����� ��������� ��������� ���? ����� � ���, ��� ��� Vulkan ���� ����������, � ��������� ������� ����� ��������� ��������� ������� ����. ���� �������� � ����������� �����, ������ �� `VK_STRUCTURE_TYPE_MAX_ENUM = 0x7FFFFFFF`. ����� � ����� ������������� ���� ����������� ��������, ����� ��� `VK_STRUCTURE_TYPE_BEGIN_RANGE`, `VK_STRUCTURE_TYPE_END_RANGE` � `VK_STRUCTURE_TYPE_RANGE_SIZE`.
+ `pNext` � ��������� �� ��������� ���������, ���������� �������������� ���������� �� ����������. � ������ ������ `nullptr`. � �������� ���������� ����� ���� �������, ��� `pNext` � ����������� ��������� ������ ��������� �� ������ ���������, ����������� ��� ����������. � ��� `sType` ����� ������ ���� ��������, �� ��� ������ ���������, ����������� � ����������.
+ `pApplicationName` � ��� ����������, ������� �� ������ �������. � ������ ������ ��� *Null Terminated* (��������� ������ ������ ���� `\0`) *C-������* (��������� �� char). ����� ������� `nullptr`.
+ `applicationVersion` � ������ ����������. ����� ������� `0`.
+ `pEngineName` � ��� ������������� ������ (���� ������� �������), ������� �����, ��� � ��� ����������. ����� ������� `nullptr`.
+ `engineVersion` � ������ ������������� ������. ����� ������� `0`.
+ `apiVersion` � ������ API.

������ � �������. ������ ����� ��� ���������: **�������** (*major*), **��������������** (*minor*) � **����** (*patch*). ��� �������� ������ ���� ������ `VK_MAKE_VERSION(major, minor, patch)`, ������� ��������� ��� ��� ����� � `uint32_t`. ��� ����, ����� �������� ��������� ����� �� ������, ���� ������� `VK_VERSION_MAJOR(version)`, `VK_VERSION_MINOR(version)`, `VK_VERSION_PATCH(version)`. ��� ����� ������� ������ ��� ����������, ������ � ������������� API. � �����, ������ API ����� ������ �� ������ ��������, �� �� ���� ���������� �� �����, ���� ������ ���������� ���� ��������� ������ (patch). ������� ������ ������ ������� `VK_API_VERSION_1_0` (� ���������� SDK � `VK_API_VERSION`).
���� ����� ������ ������������� ����� *vulkan.h*: `VK_HEADER_VERSION`.

������, �������� ���������. ��� ������, � ����� � ���������� ��� ����������:

	char app_name[] = "Vulkan Tutorian. Device. � GrWolf.";
	
� ����� �������� ��������� ����� �������:

	VkApplicationInfo app_info;
	memset(&app_info, 0, sizeof(app_info));
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = app_name;
	#ifdef VK_API_VERSION_1_0
	app_info.apiVersion = VK_API_VERSION_1_0;
	#else
	app_info.apiVersion = VK_API_VERSION;
	#endif
	app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	
� �����, � �������� � ������ �����, ����� �� ��������� ��� ���� �����. ��� �� �����, ����� ������� ��������� ��������� � ����� �������:

	VkApplicationInfo app_info = {
		VK_STRUCTURE_TYPE_APPLICATION_INFO,		// VkStructureType 	sType
		nullptr,								// const void 		*pNext
		app_name,								// const char 		*pApplicationName
		VK_MAKE_VERSION(1, 0, 0 ),				// uint32_t 		applicationVersion
		nullptr,								// const char 		*pEngineName
		0,										// uint32_t 		engineVersion
		VK_API_VERSION							// uint32_t 		apiVersion
	};

������, � �� ��� ��� ������ ��������� �� ���? ����� ����! �� ����� ����, ��������� �������� ����� ���� �������������� ��� ����������� ������ �/��� ����, ����� ���������� �������� ��� �������. � ���, ��� ��� ����������, ������ API ������ �� ��, ����� �� ������ ������� ������������ ����������, � ���� �����, �� ��� ������������. �� �� ���� ���� �����.
������ � ���������, ���������� �� ���������.

	typedef struct VkInstanceCreateInfo {
		VkStructureType             sType;
		const void*                 pNext;
		VkInstanceCreateFlags       flags;
		const VkApplicationInfo*    pApplicationInfo;
		uint32_t                    enabledLayerCount;
		const char* const*          ppEnabledLayerNames;
		uint32_t                    enabledExtensionCount;
		const char* const*          ppEnabledExtensionNames;
	} VkInstanceCreateInfo;
	
���������:
+ `sType` � ��� ���������. � ������ ������ `VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO`.
+ `pNext` �  ��������� �� ��������� �� ����������, ���� ������� �������. � ������ ������ `nullptr`.
+ `flags` � �����. �� ���� �� ����������, ��������������� ��� �������� �������������. � ������ ������ `0`.
+ `pApplicationInfo` � ��������� �� ���������� � ����������. ����� ������� `nullptr`.

����� ��� ���������� � ����� � �����������, � ������� ����� ��������� � ��������� �����. � ���� `nullptr` � `0`.
���������:

	VkInstanceCreateInfo instance_info;
	memset(&instance_info, 0, sizeof(instance_info));
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pApplicationInfo = &app_info;
	
������ ��������. ����� �������� ���������. ��� ����� ������� �����, ���� �������� ����� ��������.
�������� ����� ���������� � handle'�� � Vulkan. ������ ����� ����� �������� ����� ����������� `VK_DEFINE_HANDLE` ��� `VK_DEFINE_NON_DISPATCHABLE_HANDLE`, ��-�� ���� � ��������� IDE ��������� �������� ����������� (��������, CodeLite, ������� � ������� ��-�� ��� ������ ������). ������� ����� (�.�. ��������� ��� ��������������) ������������ ����� `VK_NULL_HANDLE`. ���� ���� ������� �������� ����� ��� �������:

	#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;

	#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
			#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T *object;
	#else
			#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object;
	#endif
        
��� ��� �����, ������ �������������� �� **������������** (*dispatchable*) � **�� ������������** (*non-dispatchable*). ������ ������������ � ������� ��� ������� ������, � ������� �� ��������, ������ �������� � �������� ���������������. ����� ������, ��� ��������� �� ������� ������������ ������, � ������� �� �������, ��� �� ����������� ��������� �� ������������ ������. � ����� ������, ������������� ��������: `VkInstance`, `VkPhysicalDevice`, `VkDevice`, `VkQueue`, `VkCommandBuffer`. ��� ��������� �������� �� �������������.

