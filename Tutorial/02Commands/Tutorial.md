#�������
**�������** � �����, ���� �������� �������. �� �������� ������������ ��� �� ������� �������� ����������: ����� ������ �������� � ������ ����������� � ����������. � �������, ������, ��� ���������� �����-���� ������� � ����������, �� ������ �������� ������ �������, � ������� ��� ����� � ����������� ��������. � ������ � � �����. 
##��������� ������
�� ��� �������� �������

	void vkGetDeviceQueue(
		VkDevice 	device,
		uint32_t 	queueFamilyIndex,
		uint32_t 	queueIndex,
		VkQueue* 	pQueue);
		
 + `device` � ����� ����������, � �������� �� ����� ����� ����� �������.
 + `queueFamilyIndex` � ������ ���������, �� �������� �� ���� �������.
 + `queueIndex` � ������ ������� (������� ������� ����� ��������������� �������� �������� �����������).
 + `pQueue` � ���������� ����� �������.
 
�������, ��� ����� ��������� ������� �������� � �������� �� ������������ ������� (� ����� � ������� �� �� �����������), ��� ��� ��� ����� �� ��� ����������. ���, ��� ��� �� ��������:
 
 
	VkQueue queue = VK_NULL_HANDLE;
	vkGetDeviceQueue(vkGlobals.device, vkGlobals.family_index, 0, &queue);
	
������� ���������� ������� �� ����������, ��� ������� (���������) ���������� ������. �� ������������ ��� ����� ������ � ������� ����� ����������. ��������� ���������� ����������� ������ � ����������� ����������.

##������������� �������

���� ��������, ��� ������� ������ ����� �� ������, ���������� �������

	VkResult vkQueueWaitIdle(
		VkQueue queue);
		
���������� ������� ����� ���� �����:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`
+ `VK_ERROR_DEVICE_LOST`

# �������
������� �� �������� �� �������. ��� ����������� **��������� ���**, ����� �� ���� �������� **��������� ������**, � ������� � ����� ������������ �������. ����� ����� ��������� ������ ����� ����� ��������� ����������� � �������.

**��������� �����** � ���� ������� ����������� �� ��� ����: **���������** (*primory*) � **���������** (*secondary*).

+ **���������** ��������� ����� ����� ���� ��������� �������� � �������, � ����� ����� ��������� ��������� ��������� �����, ��� �������, ��� ��������� ������� �������.
+ **���������** ��������� ����� **��** ����� ���� ��������� � ������� ��������, �� ����� ���� ������ ������� ���������.

##�����
����� �������� ��������� ����: ������� � ��������� ����� ������������ � ����� �� �������, � ����� ���� ������� ������� ������. ��������� ������ ��������� � ������� � ����� �� �������, � ����� � ���� ���� �������. **��**, ������� ���� **���������** ������� � **�� ����������** ���������� ����� ��������. ������� ������� ����� �������� ����������� ���� �����, � �� ��� ������� ����������� ��� �� ������. �������, ����� �� ���� �������, ��� ������� ���� ������� �������� ���������� ���������, ������� ��� �� ��� ������� ���������� ��������, � Vulkan ���������� �������������. � ���, ��� � ������������ � ����� � ��������� �����.

��������� ������ ����� ��� ������:

+ **�����������** (*initial*) � ��������� ������ ������� ��� ��������. ��� �� �������� ������� ������.
+ **������������** (*recording*) � ��������� ������ ������� ������ ������. ����� ������� `vkCmd...(...)` ������� � �������� ��������� ����� �������, � ������� ������������� �������.
+ **�����������** (*executable*) � ��������� ����� ������� � ����� ���� ��������� � �������.

## ��������� ����
**��������� ���** (*command pool*) � �����, �� �������� **����������** (������ *����������* (*allocate*), � �� *���������* (*create*)) ��������� ������. ��������� �������� ���� �������� ���:

	typedef struct VkCommandPoolCreateInfo {
		VkStructureType				sType;
		const void*					pNext;
		VkCommandPoolCreateFlags	flags;
		uint32_t					queueFamilyIndex;
	} VkCommandPoolCreateInfo;
	
+ `sType` � ��� ���������, `VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO`.
+ `pNext` � ��������� �� ESS (Extension-specific structure, ����������� ��������� ����������) ��� `nullptr`.
+ `flags` � ����� ����. ���������, ��� ����� �������� 0, ���� ��� �� ����� �� ���� �� ������.
+ `queueFamilyIndex` � ��������� ��������, � �������� ����� ������������ ��������� ������.

����� ������� ��������� �������� ����, ������� ������ ��������� ��������� ������ � �������, ������� ����������� ������� ���������. ����� ������ ������:

	typedef enum VkCommandPoolCreateFlagBits {
		VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = 0x00000001,
		VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = 0x00000002,
	} VkCommandPoolCreateFlagBits;
	typedef VkFlags VkCommandPoolCreateFlags;
	
+ `VK_COMMAND_POOL_CREATE_TRANSIENT_BIT` � ���������, ��� ��������� ������, ���������� � ����� ���� � ���������������. ��� ����� ���� �������� (reset) ��� ����������� (free) � ������������ �������� �����.
+ `VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT` � ���������, ��� ��������� ������, ���������� � ����� ���� ����� ���� �������� ������������� (��� ����������). � ��������� ������ ����� ����� ���������� ���� ���.

�������� ��� � ������� ���� �������:

	VkResult vkCreateCommandPool(
		VkDevice device,
		const VkCommandPoolCreateInfo* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkCommandPool* pCommandPool);
		
+ `device` � ����� ����������.
+ `pCreateInfo` � ��������� �� ���������� � ��������� ����.
+ `pAllocator` � ��������� �� ��������� `VkAllocationCallbacks`, ���������� ������ ������� ���������� �������.
+ `pCommandPool` � ���������� ����� ���������� ����.

������� ����������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

�������� ��������, ��� ������� �� ����� ~~�����~~ ������, ��� ������������� �����������. ���� ���� �� �������� �������� ������, ��� �� ����� ����� ������.

��������� ��� ����� ���� �������, � ����� ����� ����� ������������ ��� ���������� � ���� ������, �� ��� �������, ��� ��� ������ �� ����������� � �� ������� ���������� (�� �� ������ ���� � �������).

	VkResult vkResetCommandPool(
		VkDevice device,
		VkCommandPool commandPool,
		VkCommandPoolResetFlags flags);

+ `device` � ����� ����������.
+ `commandPool` � ��������� ���, ������� ���������� ��������.
+ `flags` � ����� ������.

����� ������ ����� ���� ������:

	typedef enum VkCommandPoolResetFlagBits {
		VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT = 0x00000001,
	} VkCommandPoolResetFlagBits;
	
+ `VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT` � ����������� ��� ������� � ������� ������� (� ��������� ������, ������� ����������� �� �����).

���������� ����������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

����������� ��� ����� �������:

	void vkDestroyCommandPool(
		VkDevice device,
		VkCommandPool commandPool,
		const VkAllocationCallbacks* pAllocator);
		
+ `device` � ����� ����������.
+ `commandPool` � ���, ������� ����� ���������.
+ `pAllocator` � ��������� �� ��������� `VkAllocationCallbacks`, ���������� ������ ������� ���������� �������.

������ �������� ����:

	VkCommandPoolCreateInfo pool_create_info;
	ZM(pool_create_info); //zero memory
	pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_create_info.queueFamilyIndex = vkGlobals.family_index;
	VkCommandPool pool = VK_NULL_HANDLE;
	if (vkCreateCommandPool(vkGlobals.device, &pool_create_info, NULL, &pool) != VK_SUCCESS)
		return;
	
##��������� ������

###���������� ���������� ��������

####��������� ��������� �������

������ ����� �������� ��������� ������ � ����. �� ����� �������� ����� ���������.

	typedef struct VkCommandBufferAllocateInfo {
		VkStructureType			sType;
		const void*				pNext;
		VkCommandPool			commandPool;
		VkCommandBufferLevel	level;
		uint32_t				commandBufferCount;
	} VkCommandBufferAllocateInfo;
	
	
+ `sType` � ��� ���������, `VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO`.
+ `pNext` � ��������� �� ESS.
+ `commandPool` � ���, � �������� ����� �������� ������.
+ `level` � ������� ������ (���������/���������).
+ `commandBufferCount` � ���������� �������.

������� ������ ������������ ���������� ����������:

	typedef enum VkCommandBufferLevel {
		VK_COMMAND_BUFFER_LEVEL_PRIMARY = 0,
		VK_COMMAND_BUFFER_LEVEL_SECONDARY = 1,
	} VkCommandBufferLevel;
	
+ `VK_COMMAND_BUFFER_LEVEL_PRIMARY` � ��������� ��������� �����.
+ `VK_COMMAND_BUFFER_LEVEL_SECONDARY` � ��������� ��������� �����.


	VkResult vkAllocateCommandBuffers(
		VkDevice device,
		const VkCommandBufferAllocateInfo* pAllocateInfo,
		VkCommandBuffer* pCommandBuffers);
		
+ `device` � ����� ����������.
+ `pAllocateInfo` � ��������� �� ��������� `VkAllocationCallbacks`, ���������� ������ ������� ���������� �������.
+ `pCommandBuffers` � ���������� ������ ��������� �������.

���������� ����������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

#### ����� ��������� �������

����� ����� ��������� � ������� ���� �������, ��� �������, ��� ����� ��� ������� �� ���� � ������ `VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT`.

	VkResult vkResetCommandBuffer(
		VkCommandBuffer commandBuffer,
		VkCommandBufferResetFlags flags);
		
+ `commandBuffer` � ����� ���������� ������.
+ `flags` � ����� ������.

����� ������, ������� ����� ���� ����������:

	typedef enum VkCommandBufferResetFlagBits {
		VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT = 0x00000001,
	} VkCommandBufferResetFlagBits;
	
+ `VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT` � ������������� ���� �������� � ����������� �� �������.

����� ��� ������ �� ������ ���� � �������.

���������� ����������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

#### ������������ ��������� ������

������ ����� �����������, ���� ������ ��� �� �����. �������, ����� ����� ������ ������� ����� ������ �����������������.

	void vkFreeCommandBuffers(
		VkDevice device,
		VkCommandPool commandPool,
		uint32_t commandBufferCount,
		const VkCommandBuffer* pCommandBuffers);
		
+ `device` � ����� ����������.
+ `commandPool` � ����� ����.
+ `commandBufferCount` � ���������� ��������� ������� ��� ������������.
+ `pCommandBuffers` � ������ ��������� �������, ������������ � ������.

����������� ���������� �����, ��� ��� �� ������ � Vulkan �� ��� ��������.

### ������ ��������� �������

������, ��� ������� ������� ������ ������, ����� ��������� ��������� ��������� �������:

	typedef struct VkCommandBufferBeginInfo {
		VkStructureType sType;
		const void* pNext;
		VkCommandBufferUsageFlags flags;
		const VkCommandBufferInheritanceInfo* pInheritanceInfo;
	} VkCommandBufferBeginInfo;
	
+ `sType` � ��� ���������, `VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO`.
+ `pNext` � ��������� �� ESS.
+ `flags` � ����� ������.
+ `pInheritanceInfo` � ���������� � ������������. ������������, ���� ������������ ����� � ���������. ���� ��� ��������� �����, ������ �������� ������������.

����� ����� ���� ������:

	typedef enum VkCommandBufferUsageFlagBits {
		VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT = 0x00000001,
		VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT = 0x00000002,
		VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT = 0x00000004,
	} VkCommandBufferUsageFlagBits;

+ `VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT` � ����, ����������,��� ����������� ������� ����� ���������� ������ ���� ���, � ��������� ����� ����� ������� � ������� ����� ����� ������ ���������.
+ `VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT` � ��������, ��� ��������� ��������� ����� ����� ��������� ������ ������� ��������� (��� ��� �����, � ��� ������������ � ����� � ��������� ������). ���� ��� ��������� ��������� ����� � ���� ������������.
+ `VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT` � � ������ ���������� ���������� ������, ���� ��������, ��� ����� ����� ��������� � ������� ��������� ��� ������ (� ��������� ������, ����� ������ ��� ����� ����� ��������� ������ ���� ���, � ����� ����� ���������� ��� ����������). � ������ �� ���������, ���������� ����� ����� ���� ��������� (�.�. ����� � ����������� ������ ���������) � ������ ��������� ��������� ��� (� ��������� ������, ����� ������������ ���������� � ����� �� ���������, � ������ ������� ���������� ��� ��������� ��� ����� ������, ������ ����� ����������� ���� � ��� �� ��������� ������ ������ ���������� ��������� ���).

� ���, ���� �� ���������� ��������� ��������� �����, �� ��� �������� ���������� � ������������:

	typedef struct VkCommandBufferInheritanceInfo {
		VkStructureType sType;
		const void* pNext;
		VkRenderPass renderPass;
		uint32_t subpass;
		VkFramebuffer framebuffer;
		VkBool32 occlusionQueryEnable;
		VkQueryControlFlags queryFlags;
		VkQueryPipelineStatisticFlags pipelineStatistics;
	} VkCommandBufferInheritanceInfo;


+ `sType` � ��� ���������, `VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO`.
+ `pNext` � ��������� �� ESS.
+ `renderPass` � ���� ������ ���� `VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT`, �� ������ ���� ����� ����� ������������ ������� ���������.
+ `subpass` � ���� ������ ���� `VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT`, �� ������ ���� ������ ������������� ����������.
+ `framebuffer` � ���� ������ ���� `VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT`, �� ����� ������ ����������. ��� �� �����, ����� ������� `VK_NULL_HANDLE`, ���� ����� ����������.
+ `occlusionQueryEnable` � ��� `VK_TRUE` ��������, ��� ��������� ��������� ����� ����� ���� ������� �� ����������, � ������� ���� �������� �� ���������� (occlusion query). ���� `VK_FALSE`, �� ��������� ��������� ����� �� ������ ��������� ����� ��������.
+ `queryFlags` � ~~... ���-�� ����� �������� ������������...~~ ��������, ��� ����������� ����� ����� ���� ������������ � � ��������� ��������� ������ (� ������� �������� �� ����������). ���� ������������ ����� ���, �� �������� �  ��������� ������ ����� �� ������ ��������� ���� ����.
+ `pipelineStatistics` � ����� ����������. ���� ����������� ���� ����, �� ������, ��� ��������� ����� � ���� (��� ���) ������ ����� ��������� ���� �����. ���� ������������ ����� ���, �� ��������� ����� ����� �� ����� ��������� ����� �����.

������, �������� ��� ����������, ����� ������ ���������� �������:

	VkResult vkBeginCommandBuffer(
		VkCommandBuffer commandBuffer,
		const VkCommandBufferBeginInfo* pBeginInfo);
	
+ `commandBuffer` � ����� ���������� ������, � ������� ����� ������������ �������.
+ `pBeginInfo` � ��������� �� ��������� `VkCommandBufferBeginInfo`.

������� ���������� ��������� ��������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

������ ����� �������� ������� `vkCmd...(...)`, ������� ������� � ��������� ����� �������. ������ ���������� ����� ������� ����� ������� ��� ��������� �����, � ������� ���������� ������. ��� �������-������� �� ���������� �������� (���������������, ��� �� ����� �� �������� � ��� ����������� ���������� ������ �������, ��� ��� ����� ���� ������ ������ � �����, � �� �� ����������).

	VkResult vkEndCommandBuffer(
		VkCommandBuffer commandBuffer);
		
+ `commandBuffer` � ��������� �����, ����������� �������� ���������� ���������.

���������� �������������:
+ ������ ������������� ������ ������ ������� ���������.
+ ��� �������� ������ ���� ��������� ����� ����������� ������.

������� ����� ���������� ��� ��������:

+ `VK_SUCCESS`
+ `VK_ERROR_OUT_OF_HOST_MEMORY`
+ `VK_ERROR_OUT_OF_DEVICE_MEMORY`

� ����� � ���� ���� ���-�� ��������� �� ���, ������������ �������� ��� �� ���� �� ��������.

### �������� ��������� �������


### ������ ���������� ���������� ������

