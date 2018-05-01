import subprocess, os
for y in xrange(1, 36):
    print("\n\n**************File %d***********" %y)
    cmd = './hw6 ' + 'TestCases/test'+str(y)+'.in ' + '> ' + 'TestCases/usertest'+str(y)+'.ans'
    os.system(cmd)
    cmd = 'diff ' + 'TestCases/usertest' +str(y)+'.ans ' + 'TestCases/test'+str(y)+'.ans'
    os.system(cmd)