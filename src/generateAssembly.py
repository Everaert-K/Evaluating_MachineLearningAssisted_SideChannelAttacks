#!/usr/bin/python

instruction = "rdrand %eax;"
amount = 1000000

filename = "instruction_"+instruction.split(' ')[0]+"_"+str(amount)+".s"

f = open(filename, "w")

string = '''# execute ''' + instruction.split(' ')[0] +''' instruction '''+str(amount)+''' times.
.text
.globl	instruction_'''+instruction.split(' ')[0]+'''_'''+str(amount)+'''
.type	instruction_'''+instruction.split(' ')[0]+'''_'''+str(amount)+''', @function

instruction_'''+instruction.split(' ')[0]+'''_'''+str(amount)+''':'''

for i in range(0,amount):
    string = string+'''\n\t'''+instruction
    
string = string+'''\n\tret 
'''

f.write(string)
f.close()







