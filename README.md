# my_markdown

A little project used for exercise my coding abality.
写个小项目练练手

## Introduction 简单介绍

This project has two parts. One part is the regex of this new markup-language. The other part is a parser written by C++, which is used for generating a  corresponding HTML file of a file written by my_markdown language.

这个项目有两个部分。其中一个是my_markdown的语法部分，第二部分是一个可以把my_markdown文件转化为HTML的解析器

### Why named my_markdown 为什么叫做my_markdown

I havn't think out a new name. Maybe I will change this name after I think out a new name.

因为我还没想出来新名字，等啥时候想出来新名字的时候可能会换掉。

### Why here is this project 为什么会有这个项目

I am building a new website but I don't want to write HTML directly. Although there is a parser able to generate HTML file from a markdown file, but markdown is not able to meet some of my need.

我最近在搭网站，但我不想直接去写HTML。所以我想弄一个从其他文本标记语言生成HTML的东西。我本打算用现成的从markdown生成HTML的生成器，但是markdown没法满足我的一些需求。

So I want to create a new markup-language and a parser of this language wihch can meet my need.

所以我打算干脆自己弄一个文本标记语言好了，然后自己做一个解析器。

## Syntax of my_markdown 此语言的语法

Please read file `my_markdown_en.wikitext` in this repo.

请阅读`my_markdown_zh.wikitext`文件

### Something new? 此语言的不同之处？

One is template. I want to a build a markup-language able to use  template as used in wikitext.

其中之一是模板，类似于像wikitext里的模板。

## Introduction for repo 对项目的介绍

The directory `src` is all resource file of this repo.

`src`目录里面存储着所有的源文件。

The directory `test` storage all file used for me to test some function, method and regex of C++.

`test`目录下的文字都是我用来测试C++的函数、方法和语法的。

### How to get executable file 如何获得可编译文件

```bash
g++ my_markdown.cpp -o main.exe 
```

## Work together? 想要合作？

I havn't planned for working together.
暂时还不打算合作。
