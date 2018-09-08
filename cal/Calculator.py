#!/usr/bin/python
import re
print "Calculator initialize ok...."

num_stack = []
op_stack = []
ans = 0

regex = re.compile(r'[\d\.]+|[\+\-\*/\(\)]')

def _compute(a,b,op):
    if op=='+':
        return a+b
    elif op=='-':
        return a-b
    elif op=='*':
        return a*b
    elif op=='/':
        return a/b
    else:
        return None

_level = {
    '+': 0,
    '-': 0,
    '*': 1,
    '/': 1
}

def _operate(item=''):
    global ans

    if item=='':
        while len(op_stack):
            b = num_stack.pop()
            a = num_stack.pop()
            op = op_stack.pop()
            num_stack.append(_compute(a,b,op))
        ans = num_stack.pop()
    elif re.match(r'[\d\.]+',item):
        num_stack.append(float(item))
    else:
        if not len(op_stack) or item=='(' or op_stack[-1]=='(':
            op_stack.append(item)
        elif item==')':
            while op_stack[-1]!='(':
                b = num_stack.pop()
                a = num_stack.pop()
                op = op_stack.pop()
                num_stack.append(_compute(a,b,op))
            op_stack.pop()
        else:
            if _level[item]<=_level[op_stack[-1]]:
                b = num_stack.pop()
                a = num_stack.pop()
                op = op_stack.pop()
                num_stack.append(_compute(a,b,op))
            op_stack.append(item)

def cal(expression):
    splitStr = regex.findall(expression)
    for tmp in splitStr:
        _operate(tmp)
    _operate()
    return ans

def clear():
    global num_stack,op_stack,ans

    num_stack = []
    op_stack = []
    ans = 0

#for test
if __name__=='__main__':
    print cal('(1+2)*3/6')
    print op_stack
    print num_stack