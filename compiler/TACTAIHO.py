import sys
import subprocess

#print(sys.argv[0])
tempvars = []

a = '''push 0
goto ?LEfact
?LSfact:
push 0
[0]=[3]==4
if not [0] pop goto ?L2
[1]=1
pop 0
return
pop 0
goto ?L1
?L2:
push 0
push 0
[0]=[4]-1
push [0]
pop 1
push 0
call ?LSfact
[2]=[0]
pop 1
pop 1
[0]=[3]*[0]
[2]=[0]
pop 1
pop 0
return
pop 0
?L1:
pop 0
return
?LEfact:
goto ?LEp2
?LSp2:
push 0
[0]=[2]*2
print [0]
pop 1
return
?LEp2:
push 0
push 6
push 0
call ?LSfact
[2]=[0]
pop 1
pop 1
[1]=[0]
pop 1
print [0]
push [0]
call ?LSp2
pop 1





'''

if (len(sys.argv) > 1):
    f = open(sys.argv[1], 'r')
    a = f.read()
    f.close()


b = ''
insts = a.split('\n')
rds = "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm1234567890#[]"
rds2 = "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm#[]"

opdict = {
    '+': 'add',
    '-': 'sub',
    '*': 'mul',
    '/': 'div',
    '%': 'mod',
    '&': 'and',
    '|': 'or',
    '^': 'xor',
    '<': 'sclt',
    '>': 'scgt',
    '<=': 'sclte',
    '>=': 'scgte',
    '!=': 'scne',
    '==': 'sce'
    }

for k in range(len(insts)):
    rawinst = insts[k].strip()
    
    if (rawinst == ''):
        continue
    if (rawinst == 'return'):
        b += 'ret\n'
    g = rawinst.find(' ')
    if (rawinst.find(':') != -1):
        b += rawinst + 'pass\n'
        continue
    if (g != -1):
        actioncode = rawinst[:g]
        if (actioncode == 'push'):
            q = rawinst.find('=')
            if(q == -1):
                varname = rawinst[g+1:].strip()
                if (varname.find('[') == -1):
                    b += 'push ' + varname + '\n'
                else:
                    numvar1 = '[' + str(int(varname[varname.find('[')+1:varname.find(']')])+1) + ']'
                    b += 'push 0\n'
                    b += 'mov [0], ' + numvar1 + '\n'
            else:
                varname = rawinst[g+1:q]
                b += 'push ' + varname + ',' + rawinst[q+1:] + '\n'
        elif (actioncode == 'goto'):
            b += 'jmp ' + rawinst[g+1:].strip() + '\n'
        elif (actioncode == 'if'):
            
            lab = rawinst[rawinst.rfind(' '):].strip()
            if (rawinst.find('pop') == -1):
                var = rawinst[rawinst.find('not')+3:rawinst.find('goto')].strip()
                b += 'cmp ' + var + ',0\n'
            else:
                var = rawinst[rawinst.find('not')+3:rawinst.find('pop')].strip()
                b += 'cmpp ' + var + ',0\n'
                
            b += 'jie ' + lab + '\n'
        else:
            b += rawinst + '\n'
    else:
        if (rawinst[0] == '~'):
            b += 'not ' + rawinst[1:] + '\n'
            continue
        q = rawinst.find('=')
        if (q != -1):
            var1 = rawinst[:q];
            if (var1[0] == '#'):
                if (not tempvars.count(var1)):
                    tempvars.append(var1)
            l = q + 1
            var2 = ""
            while (rawinst[l] in rds):
                var2 += rawinst[l]
                l += 1
                if (l == len(rawinst)):
                    break
            if (l == len(rawinst)):
                if (var2[0] in rds2):
                    b += 'mov ' + var1 + ',' + var2 + '\n'
                else:
                    b += 'set ' + var1 + ',' + var2 + '\n'
            else:
                operand = ""
                while (rawinst[l] not in rds):
                    operand += rawinst[l]
                    l += 1
                var3 = rawinst[l:]
                if (var2 == var1):
                    b += opdict[operand] + ' ' + var1 + ',' + var3 + '\n'
                else:
                    numvar1 = var1
                    if (numvar1.find('[') != -1):
                        numvar1 = '[' + str(int(var1[var1.find('[')+1:var1.find(']')])+1) + ']'
                    numvar2 = var2
                    if (numvar2.find('[') != -1):
                        numvar2 = '[' + str(int(var2[var2.find('[')+1:var2.find(']')])+1) + ']'
                    numvar3 = var3
                    if (numvar3.find('[') != -1):
                        numvar3 = '[' + str(int(var3[var3.find('[')+1:var3.find(']')])+1) + ']'
                    b += 'push 0\n'
                    b += 'mov [0],' + numvar2 + '\n'
                    b += opdict[operand] + ' [0],' + numvar3 + '\n'
                    b += 'mov ' + numvar1 + ',' + '[0]\n'
                    b += 'pop 1\n'
                    
                    #b += 'mov #ET,' + var2 + '\n'
                    #b += opdict[operand] + ' #ET,' + var3 + '\n'
                    #b += 'mov ' + var1 + ',' + '#ET\n'
                
fv = ""
for i in tempvars:
    fv += "var " + i + '\n'

b = fv + b

if (len(sys.argv) > 1):
    tyg = sys.argv[1][:sys.argv[1].rfind('.')]+'.aiho'
    f = open(tyg, 'w')
    f.write(b)
    f.close()
    if (len(sys.argv) > 2):
        z = '"' + sys.argv[1][:sys.argv[1].rfind('\\')] + '\\aa.bat" ' + '"' + tyg + '"'
        print (z)
        j = subprocess.Popen(z)
