#这是一个长度转换器主要用来把英寸转换成毫米
print("这是一个长度转换器主要用来把英寸转换成毫米")
while(True):
    print("请输入你想要转换的英寸数")
    inch_number=input()
    mm_number=(float(inch_number))*254
    print("结果是"+str(mm_number)+"mm")
