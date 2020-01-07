#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
private:
	GLFWwindow* window;
	VkInstance instance;

public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "TAS Engine - Vulkan dev", nullptr, nullptr);

	}

	void initVulkan() {
		createInstance();

	}

	void createInstance() {
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "available extensions:" << std::endl;

		for (const auto& extension : extensions) {
			std::cout << "\t" << extension.extensionName << std::endl;
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		verifyExtensionFullCapabilitiesReached(glfwExtensions, &glfwExtensionCount, &extensions);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void verifyExtensionFullCapabilitiesReached(const char** retrievedExtensions, uint32_t* retrievedCount, std::vector<VkExtensionProperties>* availableExtensions) {
		std::vector<const char*> missingExtensions;
		for (const auto& avail : *availableExtensions) {
			bool found = false;
			for (int num = 0; num < *retrievedCount; num++) {
				found = strcmp(retrievedExtensions[num], avail.extensionName);
			}
			if (!found) {
				const char* missing = avail.extensionName;
				missingExtensions.push_back(missing);
			}
		}

		std::cout << "\n___________WARNING_________" << std::endl;
		std::cout << "Following extensions are unsupported by this machine" << std::endl;
		for (auto & ext : missingExtensions) {
			std::cout << "\t" << ext << std::endl;
		}
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	/*
		After following this tutorial, you could implement automatic resource management by overloading std::shared_ptr for example. 
		Using RAII (https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization) to your advantage is the recommended approach for larger Vulkan programs,
		but for learning purposes it's always good to know what's going on behind the scenes.
	*/
	void cleanup() {
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}