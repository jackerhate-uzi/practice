# 基础了解

编译：源文件编译成中间代码文件，在unix下是.o文件

链接：把大量.o文件合成执行文件

变量：可以声明一个变量，这样在makefile中可以以$(变量名)来使用变量

make自动推导：make看到一个[.o]文件，会自动添加[.c]文件，以及cc -c [.c]

清空目标文件：.PHONY表示伪目标

命令：如果不换行，就用分号隔开；如果换行，则用tab键开头；如果命令太长，用\作为换行符

通配符：支持* ? [...]

文件搜寻：制定特殊变量VPATH,可以用冒号分割目录

伪目标：用.PHONY指明“伪目标”，伪目标不要和文件同名，要运行伪目标必须显示执行，例如make clean

> 将伪目标放在第一个作为默认目标，如果将若干个目标作为依赖，可以达到一口气生成多个目标的目的

伪目标也可以作为依赖

**$<**:依赖目标集 **$@**:目标集 目标集和依赖集都应该有%这个字符

# 命令书写

## 显示命令

1. make会显示命令行，在命令之前加上@隐藏命令
2. 参数-n --just-print只显示命令，不执行命令
3. -s --silent全面禁止命令显示

## 命令执行

如果要让上一条命令的结果用于下一条命令，用分号间隔

## 命令出错

如果一个规则中的某一条命令出错，make就会终止当前规则；

如果想忽略命令出错，1. 就在命令行前加“-”（减号）2. -i  --ignore-errors参数

终止当前规则，继续执行其他规则 -k --keep-going

## 嵌套执行make

export传递变量，unexport不传递

定义命令包define——endef

# 变量

## 变量基础知识

1. 变量声明时要赋值，使用时用（）或者{}，如果要用$,则使用$$
2. 变量就是“替代”
3. 可以用变量定义变量，如果是=，前面的变量可以使用未定义的变量；如果是：=，则只能用已定义的变量
4. 可以用#操作符表示变量定义的终止；？=表示如果有定义，则什么都不做，如果没有定义就定义

## 变量高级用法

1. 替换。$(var:a=b) 把变量var中所有以a**结尾**的替换为b
2. 把变量的值在当成变量。
3. 用+=追加变量
4. 用override设置make命令行参数
5. 用define定义多行变量
6. 设置目标变量可以达到“由该目标引起的所有规则均使用该变量”，模式变量就是用%推广目标变量

## 条件判断

ifeq ifneq

# 函数

## 字符串处理函数

1. 替换函数 $(subst from,to,text) 把text中的from替换为to
2. 模式替换patsubst
3. $(strip string)去掉string开头和结尾的空字符
4. $(findstring find,in) 在in中寻找find，找到返回find，找不到返回空字符
5. filter 模式过滤，可以有多个模式，保留符合模式的字符串
6. filter-out 反过滤，去除符合模式的子串
7. sort 给单词升序排序
8. word n 取第n个单词 wordlist 取某一段 words 统计单词个数 firstword 取第一个单词

## 文件名操作函数

1. dir names 取出names中的目录部分 notdir 取文件函数
2. suffix 取后缀函数 basename 取前缀函数 addsuffix 加后缀函数 addprefix 加前缀函数
3. join 把后者一一对应加到前者尾部

## foreach

函数为$(foreach value,list,text)，将list中的每个单词取到text的表达式中，结果用空格分开

## if

就是条件判断函数

## call

把参数放到函数里面去执行

## origin

返回值是变量的来源

1. undefined：未定义
2. default：默认变量
3. file：变量定义在makefile中
4. command line：变量定义在命令行
5. override：被override重新定义
6. automatic：自动化变量

## SHELL函数

把执行操作系统shell以后的函数作为结果返回

## make控制函数

1. error：执行以后产生错误并退出
2. warning：输出警告信息，并继续执行

# make

1. -0成功执行 -1错误退出 -2使用了-q参数

2. -f 指定makefile

3. 第一个目标是终极目标

4. 伪目标书写规则

   1. all 所有目标的目标
   2. clean 清楚所有make创建的文件
   3. install 安装编译好的程序
   4. print 列出改变过的源文件
   5. tar 将源文件打包
   6. dist 把tar打包成z或者gz
   7. TAGS 更新所有的目标
   8. check test 测试makefile

   ## 检查规则

   1. -n --just-print --dry-run --recon不执行命令，只显示
   2. -t --touch 假装编译过目标并更新时间
   3. -q --question 寻找目标，如果目标存在什么都不做，如果不存在输出错误信息
   4. -W --what-if --assume-new --new-file 格局根据规则推导来运行依赖于该文件的命令

   ## make参数

   1. -b -m忽略make兼容性
   2. -B --always-make 重编译
   3. -C --directory 读取指定目录
   4. -debug[=\<options\>]  输出调试信息，模式可选
      1. a all，输出所有
      2. b basic，输出基础信息
      3. v verbose，比b多一些
      4. i implicit，输出所有隐含规则
      5. j jobs 输出执行规则的详细信息，例如PID和返回码
      6. m makefile，输出make对makefile的操作信息
   5. -d 相当于-debug=a
   6. -e --environment-overrides 指明环境变量覆盖makefile中定义的变量的值
   7. -f --file --makefile 指定执行的makefile
   8. -h --help 显示帮助信息
   9. -i --ignore-errors 执行时忽略所有错误
   10. -I --include-dir 指定一个被包含makefile的搜索目标
   11. -j --jobs 指定同时运行命令的个数，没有就取最大
   12. -k --keep-going 出错也不停止
   13. -l --load-average 指定make运行命令的负载
   14. -o --old-file --assume-old 不重新生成指定的文件，及时他的依赖新于他
   15. -p --print-data-base 输出makefile所有数据
   16. -r --no-builtin-rules 禁止使用隐含规则
   17. -R --no-builtin-variables 禁止使用作用在变量上的隐含规则
   18. -S --no-keep-going --stop 取消-k选项的作用
   19. -v --version 输出make版本信息
   20. -w --print-directory 输出运行makefile之前和之后的信息
   21. --no-print-directory 禁止-w
   22. --warn-undefineed-variables 只要发现有未定义变量，就输出警告信息

