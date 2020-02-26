# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.1.5'

authors = ['ben.skinner',
           'daniel.flood',
           'wen.tan']

requires = ['turret_lib', 'usd']

private_build_requires = []

variants = []


def commands():
    env.TF_DEBUG = "PLUG_*"
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd')
    env.PATH.append('{root}/plugin/usd')
    env.TURRET_SERVER_IP = "127.0.0.1"
