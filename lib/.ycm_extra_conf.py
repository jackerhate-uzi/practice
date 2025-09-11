import os
import ycm_core

def Settings( **kwargs ):
    return {
        'flags': [
            '-Wall',
            '-Wextra',
            '-Werror',
            '-I', '.',
            '-isystem', '/usr/include',
            '-isystem', '/usr/local/include',
        ],
    }
