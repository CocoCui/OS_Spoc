memdata = open("data.txt")
lines = memdata.readlines()
mem = []
pdbr = 544
for l in lines:
    l = l.split(":")[1]
    data = []
    for i in l.split(' '):
        if ( len(i) > 1):
            data.append(i)
    mem.extend(data)

pdt_list = mem[pdbr:pdbr+32]
def convert(addr):
    print 'Virtual Address',addr
    addr = int(addr,16)
    pde_idx = addr>>10
    pde = int(pdt_list[pde_idx],16)
    pde_valid = pde >> 7
    pde_pfn = pde & 127
    print '  --> pde index:' + str(hex(pde_idx)) + '  pde content:(valid ' + str(pde_valid) + '  pfn ' + hex(pde_pfn) + ')'
    if pde_valid == 0:
        print '    --> Fault (page directory entry not valid)'
        return
    pte = int(mem[pde_pfn * 32 + ((addr & 1023) >> 5) ],16)
    pte_valid = pte >> 7
    pte_pfn = pte & 127
    print '    --> pte index:' + str(hex((addr & 1023) >> 5)) + '  pte content:(valid ' + str(pte_valid) + '  pfn ' + hex(pte_pfn) + ')'
    if pte_valid == 0:
        print '      --> Fault (page table entry not valid)'
        return
    pt = mem[pte_pfn * 32 + (addr & 31)]
    pa = (pte_pfn * 32 ) + (addr & 31)
    print '      --> Translates to Physical Address ' + str(hex(pa)) + ' --> Value: ' + pt

if __name__ == '__main__':
    addr_list = ['6c74','6b22','03df','69dc','317a','4546','2c03','7fd7','390e','748b']
    for a in addr_list:
        convert(a)
