# 作る機能

## まず目指すもの

- モーションデータ可視化
- マウスキーボード操作
- dear imguiによるUI

## 将来的に目指すもの

- 複数モデル読み込み
- 独立した設定ウィンドウ

# 設計

Renderer

- init_vulkan_instance()
- init_vulkan_device(vk_surface)
- init_renderer()  // vulkan instanceとvulkan deviceを先に初期化しないとエラー
- Vulkan Instance
- Device
- Physical Device
- RenderData
    - Graphics Pipeline
    - Render Pass
    - Frame Buffer
- Command Buffer
- Descriptor Set
- draw(scene, window)

Window

- GLFW Window
- Input
    - mouse input
    - keyboard input
- Surface
- Swapchain

Scene

- Mesh[]
- Camera
    - view matrix
    - projection matrix

Mesh

- Vertex[]
- index list
- Transformation
    - offset
    - rotation
- submesh list: Mesh[]

Vertex

- x, y, z
- color
- model index (bone id)

Application

- Window
- Renderer instance
- Animator instance
- etc...

BVHModelLoader

- load bvh file and generate Mesh

Animator

- manage animation time
- update Mesh transformations
