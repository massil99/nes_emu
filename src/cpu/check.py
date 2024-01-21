import re

class Line:
	def __init__(self):
		self.a = ''
		self.x = ''
		self.y = ''
		self.p = ''
		self.sp = ''
		self.inst = ''
		self.add = ''
	def __repr__(self):
		return "A:{} X:{} Y:{} P:{} SP:{} {} {}".format(self.a, self.x, self.y, self.p, self.sp, self.add, self.inst)


def parse_log(x, lx):
	m = re.search(r'A:\([0-9a-f]{2}\)', x)
	x = re.sub(r'A:\([0-9a-f]{2}\)', '', x)
	lx.a = m.group(0)[3:-1].upper()

	m = re.search(r'X:\([0-9a-f]{2}\)', x)
	x = re.sub(r'X:\([0-9a-f]{2}\)', '',  x)
	lx.x = m.group(0)[3:-1].upper()

	m = re.search(r'Y:\([0-9a-f]{2}\)', x)
	x = re.sub(r'Y:\([0-9a-f]{2}\)', '',  x)
	lx.y = m.group(0)[3:-1].upper()

	m = re.search(r'SP:\([0-9a-f]{2}\)', x)
	x = re.sub(r'SP:\([0-9a-f]{2}\)', '', x)
	lx.sp = m.group(0)[4:-1].upper()

	m = re.search(r'P:\([0-9a-f]{2}\)', x)
	x = re.sub(r'\sP:\([0-9a-f]{2}\)', '', x)
	lx.p = m.group(0)[3:-1].upper()

	m = re.search(r'[0-9a-f]{4}', x)
	x = re.sub(r'[0-9a-f]{4}', '', x)
	lx.add = m.group(0).upper()

	m = re.search(r'[a-zA-Z0-9]{3,5}', x)
	x = re.sub(r'[a-zA-Z0-9]{3,5}', '', x)
	lx.inst = m.group(0)[:3].upper()
	
def parse_ref(y, ly):
	m = re.search(r'[A-Z0-9]{4}', y)
	y = re.sub(r'[A-Z0-9]{4}', '|', y)
	ly.add = m.group(0).upper()

	m = re.search(r'[A-Z]{3}', y)
	y = re.sub(r'[A-Z]{3}', '|', y)
	ly.inst = m.group(0).upper()

	m = re.search(r'A:[0-9A-F]{2}', y)
	y = re.sub(r'A:[0-9A-F]{2}', '|', y)
	ly.a = m.group(0)[2:].upper()

	m = re.search(r'X:[0-9A-F]{2}', y)
	y = re.sub(r'X:[0-9A-F]{2}', '|', y)
	ly.x = m.group(0)[2:].upper()

	m = re.search(r'Y:[0-9A-F]{2}', y)
	y = re.sub(r'Y:[0-9A-F]{2}', '|', y)
	ly.y = m.group(0)[2:].upper()

	m = re.search(r'P:[0-9A-F]{2}', y)
	y = re.sub(r'\sP:[0-9A-F]{2}', '|', y)
	ly.p = m.group(0)[2:].upper()

	m = re.search(r'SP:[0-9A-F]{2}', y)
	y = re.sub(r'SP:[0-9A-F]{2}', '', y)
	ly.sp = m.group(0)[3:].upper()

ref = open("./ref")
log = open('./logs')

lx = Line()
ly = Line()

i = 1
for x in log:
	y = ref.readline()
	parse_log(x, lx)
	parse_ref(y, ly)

	if lx.a != ly.a or lx.x != ly.x or lx.y != ly.y or lx.p != ly.p or lx.sp != ly.sp or lx.add != ly.add or lx.inst != ly.inst:
		print('line({})'.format(i))
		print('log: {}'.format(lx))
		print('ref: {}'.format(ly))
		rep = input('> ')
		if rep == 'q':
			break
	i += 1

ref.close()
log.close()
