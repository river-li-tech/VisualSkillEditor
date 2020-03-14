1.生成pro文件
visual studio工程中，选择sloution，右键点击"create base pro"

2.在pro文件中添加
TRANSLATIONS += I18N/en.ts \
                I18N/zh.ts

3.打开  Qt 5.6.3 64-bit for Desktop (MSVC 2013)
  跳转到pro所在目录
  
4.在cmd中执行命令：
lupdate -verbose SkillEditor.pro

5.打开语言翻译工具
linguist 

6.生成.qm文件（.qm是经过.ts转换而成的二进制机器语言）
lrelease –verbose SkillEditor.pro


