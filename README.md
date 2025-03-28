# MyQtWidgetLibrary

# 使用说明
- 支持MSVC、MinGW，release和debug编译
- 修改build.bat中的Qt，改为你的Qt安装目录的绝对路径
- 然后根据需要分别设置MSVC或者MinGW的cmake目录的绝对路径
# MSVC构建
- build.bat修改完成后直接运行即可，MSVC构建后还需运行install.bat打包相关的库文件到执行目录才能在VisualStudio中调试项目
# MinGW构建
- 使用QtCreator打开，不支持VisualStudio


# 运行效果图
- 播放器UI示例
  - 主题色彩参考虎牙客户端
  - 使用自定义控件：三个Handle的QSlider，实现视频片段选择播放
![Image](https://github.com/user-attachments/assets/2fab8ff7-f7f6-4a6a-9ffb-0182dffbd702)
  - 普通的自定义风格的QSlider
![Image](https://github.com/user-attachments/assets/a84bbb45-0dbd-4fdf-b83b-3d0b8e836a10)
  - 悬浮Dialog效果
![Image](https://github.com/user-attachments/assets/fab1e092-9f11-4814-8878-41e1e05482bc)
  - 获取电脑摄像头资源
![Image](https://github.com/user-attachments/assets/b2fa10c8-4a6c-483d-9f56-3ff1992e9144)
  - 桌面捕获控件示例
![Image](https://github.com/user-attachments/assets/72a693c2-1aa6-4172-a787-045c0e40cf37)
![Image](https://github.com/user-attachments/assets/cc7da698-ef1c-427c-9d45-c2bf9b16abfc)
  - 自定义风格的FileDialog
![Image](https://github.com/user-attachments/assets/cfe10fec-ad9d-4e14-932c-e1400a37d0dd)




