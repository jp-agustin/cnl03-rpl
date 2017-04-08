# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('rpl', ['internet'])
    module.source = [
        'model/rpl.cc',
        'model/rpl-neighbor.cc',
        'model/rpl-neighborset.cc',        
        'model/rpl-header.cc',
        'model/rpl-option.cc',
        'model/rpl-objective-function.cc',
        'model/rpl-routing-table.cc',
        'helper/rpl-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('rpl')
    module_test.source = [
        'test/rpl-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'rpl'
    headers.source = [
        'model/rpl.h',
        'model/rpl-neighbor.h',
        'model/rpl-neighborset.h',  
        'model/rpl-header.h',
        'model/rpl-option.h',
        'model/rpl-objective-function.h',
        'model/rpl-routing-table.h',
        'helper/rpl-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

