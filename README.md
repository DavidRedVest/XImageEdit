# XImageEdit

[English](README_EN.md) | **中文**

基于Qt6 + C++17实现跨平台图片编辑器，采用MVC架构设计，支持macOS/Windows

![](image/app_release_v1.png) 

# 功能 

| 功能        | 说明                         |
| ----------- | ---------------------------- |
| 打开 / 保存 | 支持 PNG、JPG、BMP 格式      |
| 画笔        | 自由绘制，可调笔刷大小与颜色 |
| 橡皮擦      | 局部擦除，基于原图像素还原   |
| 矩形        | 拖拽绘制矩形边框             |
| 撤销 / 重做 | 基于命令队列的多步历史记录   |

# 架构 

采用 MVC 设计模式，各层职责清晰、模块可独立替换（如将 Qt 替换为 MFC 只需重新实现 `IView`）。

```
┌─────────────────────────────────────────────┐
│  View                                        │
│  MyImageEdit (主窗口)  XImage (画布 QWidget) │
│  XEditView (IView 实现，双缓冲渲染)           │
└───────────────────┬─────────────────────────┘
                    │ IController (Facade)
┌───────────────────▼─────────────────────────┐
│  Controller                                  │
│  IController — 统一对外接口                  │
│  XControllerFactory — 抽象工厂，创建 MVC     │
└───────────────────┬─────────────────────────┘
                    │ Observer 通知
┌───────────────────▼─────────────────────────┐
│  Model                                       │
│  XModel (XSubject) — 存储坐标与绘制参数      │
│  IGraph 策略族 — XPenGraph / XEraseGraph /   │
│                   XRectGraph / XImageGraph   │
└─────────────────────────────────────────────┘
```

## 用到的设计模式

- **抽象工厂**：`IControllerFactory` / `XControllerFactory` 统一创建 M、V、C

- **单例**：`XEditView`、`XControllerFactory` 保证全局唯一实例

- **外观（Facade）**：`IController` 对外暴露简洁接口，隐藏内部 MVC 协作细节

- **观察者**：`XModel`（Subject）变化时通知 `XEditView`（Observer）触发重绘

- **策略**：`IGraph` 族在运行时按当前工具类型选择对应的绘制算法

# 环境要求 

- CMake ≥ 3.16

- Qt 6.x（Widgets 模块）

- C++17 兼容编译器（Clang / GCC / MSVC）

- clang-format（可选，用于代码格式化）

## 编译运行 

```base 
# 清除旧缓存
rm -rf build

# 配置
cmake -B build

# 编译（8 线程）
cmake --build build -j8

# 格式化代码（可选）
cmake --build build --target format

# 运行
# macOS
open build/MyImageEdit.app
# Windows
.\build\MyImageEdit.exe
```



# 扩展指南 

**添加新绘图工具（以"画圆"为例）：**

1. 在 `constants.h` 的 `XSTATUS` 枚举中添加 `XCIRCLE`
2. 新建 `include/xcirclegraph.h` 和 `src/xcirclegraph.cpp`，继承 `IGraph` 实现 `Draw()`
3. 在 `XEditView` 构造函数中增加：`views[XCIRCLE]=new XCircleGraph()` 
4. 在 `XImage` 中添加 `SetCircle()` slot，连接对应按钮

其余代码无需改动。

## 许可证

MIT License