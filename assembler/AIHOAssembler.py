import sys
import subprocess
vardict = {}
varinit = {}
varsx = []
labeldict = {}
varint = 0
inscount = 0
cbytecount = 0
codelist = []
header = b"AIHO"
code = b""
aihocode = b""

def stack_position(s):
    return int(s[s.find('[')+1:s.find(']')].strip())


def assemble_command(command):
    global vardict
    global varinit
    global varint
    global labeldict
    global code
    global inscount
    global cbytecount
    if (command.strip() == ''):
        return
    if (command.strip()[0:2] == '//'):
        return
    re = command.find('//')
    if (re != -1):
        command = command[:re]
    #inscount += 1
    k = command.find(':')
    if (k == -1):
        o1 = command.strip().find(' ')
        o2 = len(command.strip())
        if (o1 != -1):
            z = o1
        else:
            z = o2
        
        action = command[:z].strip().lower()
        #print (command.strip().find(' '), command.strip().find('\n'), min(command.strip().find(' '), command.strip().find('\n')))
    else:
        label = command[:k]
        labeldict[label] = inscount
        command = command[k+1:]
        o1 = command.strip().find(' ')
        o2 = len(command.strip())
        if (o1 != -1):
            z = o1
        else:
            z = o2
        action = command[:z].strip().lower()
    #print (action)
    inscount += 1
    if (action == 'var'):
        
        comma = command.find(',')
        if (comma != -1):
            ax2 = command[comma+1:].strip()
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            varsx.append(command[z:comma].strip())
            vardict[command[z:comma].strip()] = varint
            varinit[command[z:comma].strip()] = bytes([x21, x22, x23, x24])
        else:
            varsx.append(command[z:].strip())
            vardict[command[z:].strip()] = varint
        inscount -= 1
        varint += 1
    elif (action == 'push'):
        a2 = int(command[z:].strip())
        x21 = a2%256
        a2 = a2 // 256
        x22 = a2%256
        a2 = a2 // 256
        x23 = a2%256
        x24 = a2 // 256
        codelist.append([b'E' + bytes([x21, x22, x23, x24]) , cbytecount])
        cbytecount += 5
    elif (action == 'pop'):
        a2 = int(command[z:].strip())
        x21 = a2%256
        a2 = a2 // 256
        x22 = a2%256
        a2 = a2 // 256
        x23 = a2%256
        x24 = a2 // 256
        codelist.append([b'F' + bytes([x21, x22, x23, x24]) , cbytecount])
        cbytecount += 5
    elif (action == 'add'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'A' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'a' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
        
        
        #code += b'a' + bytes([x11, x12, x21, x22]) 
    elif (action == 'sub'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'B' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'b' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    elif (action == 'sclt'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'R' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'r' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'scgt'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'S' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b's' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    elif (action == 'sclte'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'U' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'u' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
            
    elif (action == 'scgte'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'V' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'v' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'scne'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'2' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'1' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    elif (action == 'sce'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'4' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'3' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'mul'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'C' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'c' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'div'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'D' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'd' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
            
    elif (action == 'mov'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'f' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'e' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
            
    elif (action == 'set'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ax2 = command[comma+1:].strip()
        if (ax2[-1] == 'h'):
            a2 = int(ax2[:len(ax2)-2],16)
        else:
            a2 = int(ax2)
        x21 = a2%256
        a2 = a2 // 256
        x22 = a2%256
        a2 = a2 // 256
        x23 = a2%256
        x24 = a2 // 256
        
        codelist.append([ b'f' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
        cbytecount += 7
    elif (action == 'cmp'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'G' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'g' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    elif (action == 'cmpp'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'8' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'7' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    elif (action == 'and'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'N' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'n' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'or'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'O' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'o' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'xor'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'P' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b'p' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5
    
    elif (action == 'not'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        codelist.append([ b'q' + bytes([x11, x12]), cbytecount])
        cbytecount += 3
    elif (action == 'print'):
        a1 = stack_position(command[z:].strip())
        x11 = a1%256
        x12 = a1//256
        codelist.append([ b'y' + bytes([x11, x12]), cbytecount])
        cbytecount += 3
    elif (action == 'input'):
        a1 = stack_position(command[z:].strip())
        x11 = a1%256
        x12 = a1//256
        codelist.append([ b'z' + bytes([x11, x12]), cbytecount])
        cbytecount += 3
    elif (action == 'jmp'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'x' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'x', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'call'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == '5'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'5' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'5', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'ret'):
        codelist.append([ b'6', cbytecount])
        cbytecount += 1
    elif (action == 'jil'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'h' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'h', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'jig'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'i' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'i', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'jile'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'j' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'j', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'jige'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'k' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'k', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'jie'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'l' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'l', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'jine'):
        
        ax2 = command[z:].strip()
        if (ax2[0].isnumeric()):
            if (ax2[-1] == 'h'):
                a2 = int(ax2[:len(ax2)-2],16)
            else:
                a2 = int(ax2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([ b'm' + bytes([x11, x12]), cbytecount])
            cbytecount += 5
        else:
            codelist.append([ b'm', cbytecount, ax2])
            cbytecount += 5
    elif (action == 'mod'):
        comma = command.find(',')
        a1 = stack_position(command[z:comma].strip())
        x11 = a1%256
        x12 = a1//256
        ma2 = command[comma+1:].strip()
        if ma2.isnumeric():
            a2 = int(ma2)
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist.append([b'T' + bytes([x11, x12, x21, x22, x23, x24]) , cbytecount])
            cbytecount += 7
        else:
            a2 = stack_position(ma2)
            x21 = a2%256
            x22 = a2//256
            codelist.append([b't' + bytes([x11, x12, x21, x22]) , cbytecount])
            cbytecount += 5

    elif (action == 'pass'):
        codelist.append([ b'`', cbytecount])
        cbytecount += 1
def make_aihocode():
    global vardict
    global varint
    global varsx
    global code
    global header
    global aihocode
    global codelist
    varsect = b''
    header = b"AIHO"
    code = b""
    #print (varinit)
    for i in varsx:
        #print (i)
        if (varinit.get(i)):
            varsect = varsect + varinit.get(i)
        else:
            varsect = varsect + b'\x00'*4
    for i in range(len(codelist)):
        if (len(codelist[i]) != 2):
            l = codelist[i][2]
            #print (labeldict)
            xz = labeldict[l]
            #print (xz, codelist)
            a2 = codelist[xz][1]
            x21 = a2%256
            a2 = a2 // 256
            x22 = a2%256
            a2 = a2 // 256
            x23 = a2%256
            x24 = a2 // 256
            codelist[i][0] += bytes([x21, x22, x23, x24])
    for i in codelist:
        code += i[0]
    a2 = len(code)
    x21 = a2%256
    a2 = a2 // 256
    x22 = a2%256
    a2 = a2 // 256
    x23 = a2%256
    x24 = a2 // 256

    varsect = bytes([x21,x22,x23,x24]) + varsect
    a2 = len(varsect) + 4
    x21 = a2%256
    a2 = a2 // 256
    x22 = a2%256
    a2 = a2 // 256
    x23 = a2%256
    x24 = a2 // 256
    header += bytes([x21,x22,x23,x24]) + varsect
    aihocode = header + code

def assemble(path, path2):
    global vardict
    global varinit
    global varsx
    global varint
    global labeldict
    global code
    global inscount
    global cbytecount
    global codelist
    global header
    global code
    global aihocode
    vardict = {}
    varinit = {}
    varsx = []
    labeldict = {}
    varint = 0
    inscount = 0
    cbytecount = 0
    codelist = []
    header = b"AIHO"
    code = b""
    aihocode = b""
    f = open(path, 'r')
    x = f.read()
    f.close()
    t = x.split('\n')
    for i in t:
        assemble_command(i)
    #print (codelist)
    make_aihocode()
    f = open(path2, 'w+b')
    f.write(aihocode)
    f.close()

if (len(sys.argv) > 1):
    assemble(sys.argv[1], sys.argv[1] + 'b')
    z = '"' + sys.argv[0][:sys.argv[0].rfind('\\')] + '\\AIHO-VM.exe" "' + sys.argv[1] + 'b"'
    #print (z)
    a = subprocess.Popen(z)
    
