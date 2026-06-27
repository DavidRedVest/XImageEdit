# Changelog（更新日志）

所有对`XImageEdit` 项目的重要更改都会记录到这个文件中

- 使用智能指针和`C++17`

- 引入标准布局管理器

- 解决矩形绘制残影问题

  - 方案一：`paintEvent`即时挥发渲染

  - 方案二：双缓冲/双图层机制

    采用方案二

- 工程化规范：引入`Doxygen`格式注释，使用  `.clang-format` 文件

- 修复`BUG`：`XControllerFactory::CreateV()`

   每次调用都重复注册` IGraph`，导致内存泄漏，在`XEditView`中只做一次

- `QPainter* op`生命周期风险，重新封装一个函数处理

- `myimageedit.cpp`中大量重复的图标设置代码，提取一个辅助函数简化代码

- 简化`XModel::SetPara` 

- 优化MacOS中Qt图标问题

- 修正 MVC 历史逻辑：背景图不再作为可撤销步骤；打开新图会清空旧历史；新绘制后会清空 redo 栈。

- 提升可扩展性：`XEditView` 图元注册改为 `RegView<T>() + unique_ptr` 管理，新增工具更集中、更安全。

- 强化接口替换能力：给 `IControllerFactory`、`IGraph`、`IObserver`、`IView`、`XSubject` 等多态基类补了虚析构，给实现类补了 `override`。

- 增强健壮性：补了控制器空指针保护、图片路径 `QByteArray` 生命周期保护、画笔参数默认值、橡皮擦背景图检查。

- 优化 UI 代码：按钮加 tooltip，滑块使用 `AppConfig` 常量，Qt 连接改成类型安全写法。

  