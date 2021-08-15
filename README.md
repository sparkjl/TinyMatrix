
## TinyMatrix点阵控制器
> 基于STM32F103 Microcontroller，HUB75接口的点阵控制器。可通过1 x 4按键、串口指令控制LED点阵屏显示。

![](https://github.com/sparkjl/TinyMatrix/blob/main/images/Tiny%20Matrix.png)

### 1. 硬件
#### 1.1. HUB75接口定义
Led点阵板的HUB75接口，一般以DC3-16P牛角座封装形式接入。通常Led点阵板的左右两侧各有一个HUB75接口IN、OUT，以实现多块Led点阵板的组合扩展。HUB75接口中：R1、G1、B1分别为上半屏的红、绿、蓝控制信号，R2、G2、B2分别为下半屏的红、绿、蓝控制信号，A、B、C、D、E为行选择信号，CLK为数据时钟信号，LAT为数据锁存信号，OE为输出使能信号，GND为信号地。

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/HUB75-E%20interface.png">
</div>

#### 1.2. HUB75扫描方式
将行扫描信号、行选择信号进行组合控制，就实现了整个Led点阵板的扫描显示。其具体实现过程如下：

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/ezgif-4-36eb6aafa0.gif">
</div>

1. 从DATA_IN引脚（R1、G1、B1、R2、G2、B2）写入1 bit数据，将CLK引脚拉高产生上升沿将数据写入移位寄存器。如此循环m次将一行m bit数据传输至移位寄存器。
2. 将LATCH、<SPAN style="TEXT-DECORATION: overline">OE</SPAN>引脚拉高，m bit数据被从移位寄存器传输至缓存寄存器。同时缓存寄存器中数据被保持禁止从输出驱动器中输出，以使得在行选择信号切换时没有Led被点亮。
3. 切换并输出行选择信号。(初始状态时，第0行、第32行被选中。)
4. 将LATCH、<SPAN style="TEXT-DECORATION: overline">OE</SPAN>引脚拉低，m bit数据被从缓存寄存器传输至输出驱动器。同时移位寄存器中数据被锁存禁止从缓存寄存器中移出，此时对应选中行Led被点亮。

将以上步骤执行n/2次，便能实现m x n像素Led点阵板整个画面的扫描显示。如果扫描频率足够低，我们能看到逐行扫描显示的全过程：

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/scan116.gif">
</div>

基于人眼视觉暂留效应（余晖效应），我们无法分辨刷新率在24Hz以上的动态画面。如果将扫描频率设置在60Hz，我们就能看到一幅完整的静态画面。而这也就是常见的显示器的基本原理。

最后，将Led点阵板上下两个部分的R1、G1、B1、R2、G2、B2控制信号进行组合，便能基于光学RGB模型实现全彩显示。


#### 1.3. Led Matrix控制板设计
了解了HUB75接口的控制原理，接下来进行Led Matrix控制板设计。

Led Matrix控制板设计思路如下：

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/Led%20Matrix%20Controller.png" width="72%"/>
</div>

Led Matrix控制板的核心选择的是一款尺寸为 22.86mm x 53.34mm 的STM32最小系统板。其通过2 x 20Pin GPIO排针将板载STM32F103C8T6 MCU内集成的2x SPI、3x USART、2x I2C、1x CAN、37x I/O、2x ADC、4x Timer等硬件资源引出，以便外围扩展板调用。固件程序可通过SWD接口进行烧录和调试，可通过Reset键复位。板载2路Led灯，一路用于电源状态指示，一路用于程序状态指示。

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/stm32minisystem.jpg" width="72%"/>
</div>

Led Matrix控制板设计1 x 4按键用于点阵控制器的参数设置。MCU相关GPIO经由74HC245连接至HUB75接口，以增加驱动电流并将驱动电压从3.3v转换至5.0v。外挂的W25Qxx系列SPI Flash用于存储系统参数和字库数据。UART串口可用于下载系统参数和字库数据，TTL-蓝牙模块、TTL-WiFi模块通过UART串口建立与MCU间的通讯以实现控制指令、显示数据的无线透传。Led Matrix控制板由外接电源适配器或内置锂离子电池提供系统电源，直流降压电路实现系统电源从12v-> 5v-> 3.3v电压转换以给各功能单元供电。

基于以上硬件需求，将Led Matrix控制板通过Eagle PCB设计如下。至于为什么是Eagle PCB，那是因为其小巧精悍、简单易用，丰富的元件库、精美的原理图、标准vector字体，无不透露着严谨精致。可惜的是，被Autodesk收购后的Eagle 9.6.2对于3D模型的预览编辑需要通过Fusion 360来实现。

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/led_matrix_eagle_1.png">
</div>
<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/led_matrix_eagle_2.png">
</div>

### 2. 结构

Eagle 9.6.2不支持直接编辑3D封装，而只能通过Fusion 360以云托管元件库的方式导入。不想从Fusion 360中重构元件库，但又追求项目完整性，这怎么解决呢？那就选择KiCad，不仅支持3D封装的直接编辑，还能将Eagle的.sch原理图文件、.brd电路板文件转换成对应的KiCad格式文件。

使用KiCad将Led Matrix控制板的Eagle格式文件转换成KiCad格式文件，基于此添加编辑3D封装，导出Led Matrix控制板3D Step模型文件。

使用KiCad对MCU核心板重新进行layout，添加编辑3D封装，导出MCU核心板3D Step模型文件。

在Fusion 360中将Led Matrix控制板和MCU核心板进行零件装配、干涉检查。

![](https://github.com/sparkjl/TinyMatrix/blob/main/images/led_matrix_step_3.png)

在Fusion 360中将Led Matrix控制板设置为固定零件，以此为基准依据Led Matrix控制板的空间尺寸设计Led Matrix控制器的整体结构。选择亚克力板材作为外壳材质。顶部和底部亚克力板通过双通螺母柱进行连接，Led Matrix控制板和Led点阵板与底部亚克力板连接固定，四侧亚克力板与顶部和底部亚克力板通过卡扣扣合进行连接。

![](https://github.com/sparkjl/TinyMatrix/blob/main/images/led_matrix_step_4.png)

### 3. 软件
#### 3.1. RGB LED全彩显示
控制RGB LED实现全彩显示的传统方式是脉宽调制（Pulse Width Modulation），简称PWM。通过脉宽调制控制LED开关时间占比，进而实现RGB LED的亮度调节。如果对RGB模块中的三个LED进行此操作，则可以将红绿蓝三色按比例混合成对应的RGB全彩输出。对于Led Matrix Panel的全彩显示，PWM方式却不适用：这需要足够多的GPIO和定时器独立控制，需要消耗太多的硬件资源。那么我们如何通过软件方式予以解决呢？  

二进制编码调制（Binary Code Modulation），简称BCM。BCM利用二进制编码性质控制开关信号占空比。假设有一个位宽为4的二进制数：从其最低位向左移动至最高位依次表示1个时间切片、2个时间切片、4个时间切片、8个时间切片。将这4种时间切片混合，可产生分辨率为1/15的任意占空比。如此，位宽越大分辨率越高色彩越丰富。位宽为8的二进制数，可表示分辨率为1/255的任意占空比。但位宽越大，时间切片越小，意味着更高的CPU占用率。为更好地平衡系统性能和硬件资源，本项目中BCM位宽为4。例如，4位二进制数0101表示5/15或33.3%的占空比。

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/pwmbcm.gif">
</div>

Led Matrix Panel是逐行扫描显示的，所以需要预先将图像像素色彩转换成BCM值保存至图像缓冲区。创建4个图像缓冲区，以表示BCM位宽为4情况下的4种长度的时间切片中在扫描时间范围内哪些时间切片需要点亮LED。将这4个图像缓冲区构成的4个颜色通道Plane，进行图像融合就构成了一幅完整的静态图像。

<div align="center">
    <img src="https://github.com/sparkjl/TinyMatrix/blob/main/images/imageplanes.png">
</div>

