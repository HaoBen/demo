# 一个简单的REST服务器
>基于cpprestsdk开发

## 1. 编译
执行`make`

## 2. 使用
`./restserver [port]`，默认监听8080端口

## 功能结构

1. `/rest/ask`，问答服务

```json
请求:
{
    mesAsk: String
    asker: String
}
应答：
{
    mesReply: String
}
```

2. `/rest/calc`，计算器服务

```json
请求：
{
    left: Number,
    right: Number,
    OpCode: Number
}
应答：
{
    res: Number,
    message: String    // OK表示成功，否则表示出错了
}
```
