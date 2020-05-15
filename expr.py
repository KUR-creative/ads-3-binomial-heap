import subprocess as sp
import sys

import numpy as np
import matplotlib.pyplot as plt
import funcy as F
import yaml
from tqdm import tqdm

#tup = lambda f: lambda argtup: f(*argtup)

def expr_result(num_data, num_data_m):
    ''' experiment result in milli second '''
    return yaml.safe_load(
        sp.check_output(
            ['./main', str(int(num_data)), str(int(num_data_m))],
            universal_newlines=True))
from pprint import pprint
#pprint( expr_result(100000, 3))

def push_pop():
    #push, pop: asc / dec / rand
    min_num = 10
    max_num = 200000
    step = 5000
    num_datas = list(range(min_num, max_num, step))
    result_dics = list(tqdm(
        map(lambda n: expr_result(n, 3), num_datas),
        total = len(num_datas)
    ))
    exprs = F.join_with(list, result_dics)
    #return num_datas, exprs

    pprint(exprs)
    print(num_datas)

    y_keys = F.lremove(
        lambda key: 'merge' in key or 'pop' in key, 
        exprs.keys())

    gradient_dic = {}
    for key in sorted(y_keys):
        plt.plot(num_datas, exprs[key], label=key,
                 marker='.' if 'bh' in key else 'x',
                 linestyle='-' if 'bh' in key else '--')
        gradient_dic[key] = np.polyfit(num_datas, exprs[key], 1)[0]

    pprint(gradient_dic)
    plt.xlabel('number of keys')
    plt.ylabel('milli seconds')
    plt.legend()
    plt.show()


    y_keys = F.lremove(
        lambda key: 'merge' in key or 'push' in key, 
        exprs.keys())

    gradient_dic = {}
    for key in sorted(y_keys):
        plt.plot(num_datas, exprs[key], label=key,
                 marker='.' if 'bh' in key else 'x',
                 linestyle='-' if 'bh' in key else '--')
        gradient_dic[key] = np.polyfit(num_datas, exprs[key], 1)[0]

    pprint(gradient_dic)
    plt.xlabel('number of keys')
    plt.ylabel('milli seconds')
    plt.legend()
    plt.show()

def merge():
    min_num = 10
    max_num = 5000
    step = 100
    num_datas = list(range(min_num, max_num, step))
    result_dics = list(tqdm(
        map(lambda n: expr_result(3, n), num_datas),
        total = len(num_datas)
    ))

    def avrg_merge_result(dic):
        def avrg(dics):
            return sum(map(lambda d: d['time'], dics)) / len(dics)
        dic['h.merge.2rand'] = avrg(dic['h.merge.2rand'])
        dic['bh.merge.2rand'] = avrg(dic['bh.merge.2rand'])
        return dic
    result_dics = F.lmap(avrg_merge_result, result_dics)
    print(result_dics)
    exprs = F.join_with(list, result_dics)
    #pprint(exprs)

    y_keys = F.lremove(
        lambda key: 'pop' in key or 'push' in key, 
        exprs.keys())
    #print(y_keys)

    gradient_dic = {}
    for key in sorted(y_keys):
        plt.plot(num_datas, exprs[key], label=key,
                 marker='.' if 'bh' in key else 'x',
                 linestyle='-' if 'bh' in key else '--')
        gradient_dic[key] = np.polyfit(num_datas, exprs[key], 1)[0]

    pprint(gradient_dic)
    plt.xlabel('max number of keys')
    plt.ylabel('milli seconds')
    plt.legend()
    plt.show()

merge()
