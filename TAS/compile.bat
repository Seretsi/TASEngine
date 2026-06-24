md .\shaders_compiled
"%VULKAN_SDK%\Bin\glslc.exe" shaders/shader.vert -o shaders_compiled/vert.spv
"%VULKAN_SDK%\Bin\glslc.exe" shaders/shader.frag -o shaders_compiled/frag.spv
pause