#include "twpch.h"

// This file exists just to properly build ImGui

#define GLFW_EXPOSE_NATIVE_WIN32

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"

#include "imgui.cpp"
#include "imgui_tables.cpp"
#include "imgui_widgets.cpp"