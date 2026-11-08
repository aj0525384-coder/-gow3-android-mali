
#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <sstream>

static std::string vkVersion(uint32_t version) {
    std::ostringstream out;
    out << VK_API_VERSION_MAJOR(version) << "."
        << VK_API_VERSION_MINOR(version) << "."
        << VK_API_VERSION_PATCH(version);
    return out.str();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gpuinfo_MainActivity_getVulkanInfo(
        JNIEnv* env, jobject) {

    std::ostringstream result;

    VkApplicationInfo app{};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "GoW3 Mali Diagnostic";
    app.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &app;

    VkInstance instance = VK_NULL_HANDLE;

    VkResult status = vkCreateInstance(
        &createInfo, nullptr, &instance
    );

    if (status != VK_SUCCESS) {
        result << "Vulkan indisponivel.\n";
        result << "Codigo: " << status;
        return env->NewStringUTF(result.str().c_str());
    }

    uint32_t count = 0;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);

    result << "GO W3 ANDROID - GPU TEST\n\n";
    result << "Dispositivos Vulkan: " << count << "\n";

    for (uint32_t i = 0; i < count; i++) {
        VkPhysicalDevice device;
        vkEnumeratePhysicalDevices(instance, &count, nullptr);
        VkPhysicalDeviceProperties props{};
        VkPhysicalDevice deviceList[16]{};
        uint32_t available = count < 16 ? count : 16;

        vkEnumeratePhysicalDevices(
            instance, &available, deviceList
        );

        device = deviceList[i];
        vkGetPhysicalDeviceProperties(device, &props);

        result << "\nGPU: " << props.deviceName << "\n";
        result << "Vulkan: " << vkVersion(props.apiVersion) << "\n";
        result << "Driver: " << props.driverVersion << "\n";
        result << "Vendor ID: " << props.vendorID << "\n";
        result << "Device ID: " << props.deviceID << "\n";
    }

    vkDestroyInstance(instance, nullptr);

    return env->NewStringUTF(result.str().c_str());
}
