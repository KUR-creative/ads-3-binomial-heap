import subprocess as sp
import sys

import yaml

def expr_result(num_data, node_size):
    ''' experiment result in milli second '''
    return yaml.safe_load(
        sp.check_output(
            ['./main', str(int(num_data)), str(int(node_size))],
            universal_newlines=True))
from pprint import pprint
pprint(
    expr_result(100000, 10)
)
