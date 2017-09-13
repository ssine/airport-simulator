# 编译所需的附加库

gult就不提及了

SOIL是OpenGL一个图形读取库，用于加载纹理

将SOIL.c和SOIL.h放在VS安装文件夹下VC里面的include里

SOIL.lib放在include旁边的lib文件夹下

编译时找到VS下调试->项目属性->链接器->输入->附加依赖项，在里面添加SOIL.lib

