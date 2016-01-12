import sys
import string
import StringIO
import random


def generate_character(alphabet=string.ascii_uppercase):
    return random.choice(alphabet)

if __name__ == '__main__':

    if len(sys.argv) < 2:
        print 'Missing arguments: <total_characters>'
        exit(-1)

    total_characters = int(sys.argv[1])

    string_buffer = StringIO.StringIO()
    for idx in xrange(total_characters):
        if idx % 70 == 0:
            string_buffer.write('\n')
        string_buffer.write(generate_character())

    print '>%d TestCaseGenerator' % total_characters,
    print string_buffer.getvalue()
