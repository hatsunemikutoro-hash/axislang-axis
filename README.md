# Axis Language

 ## What is it?

 Axis is an instruction- and memory-based programming language that brings together the experience of **Assembly** and **Brainfuck**.

 Its goal is to make low-level programming much easier to learn, bringing back the enjoyment of studying low-level concepts without feeling lost.

 ## How does it work?

 Axis runs on a large memory array containing **256 positions**. Each position has its own address and value.

 The programmer's role is to manipulate this memory through different instructions in order to create various types of programs.

 > **Why would I use Axis instead of another language to learn low-level programming?**

 One of the main reasons many people avoid learning low-level programming is the difficulty that comes with it.

 Axis was designed to be the **intermediate axis** between the transparency of low-level programming and the simplicity of high-level programming, allowing beginners to understand low-level concepts without feeling overwhelmed.

 ## How to install?

 ### 1\. Clone the repository

 Open your terminal and run:

```
git clone https://github.com/hatsunemikutoro-hash/axislang-axis.git
```

 ### 2\. Open the project folder

```
cd axislang-axis
```

 ### 3\. Build the project

```
make
```

 ### 4\. Create an `.axis` file

 For example:

```
PRINT 1
PRINT 2
```

 ### 5\. Run your program

```
./axis filename.axis
```