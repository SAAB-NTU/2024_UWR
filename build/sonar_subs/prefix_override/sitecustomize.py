import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/nuc1/Desktop/2024_UWR/install/sonar_subs'
