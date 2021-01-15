#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include "cpu.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>

class System;

class GUI {
public:
  explicit GUI(System *sys) : system_(sys) {}
  ~GUI();

  void Start(int x, int y);
  void Stop();

  void Render();

 private:
  void Close();

  void DrawProfiler() const;
  void DrawCPUStatus() const;
  void DrawBreakpoints();
  void DrawMemoryInspect() const;
  void DrawDisassembler();
  void DrawVickySettings() const;
  void DrawStackInspect() const;
  void DrawDirectPageInspect() const;

  std::mutex gui_mutex_;
  std::thread gui_thread_;

  std::atomic_bool running_;
  std::chrono::time_point<std::chrono::steady_clock> next_render_time_;  

  System *system_;

  GLFWwindow *window_ = nullptr;
  ImGuiIO *io_;
};
