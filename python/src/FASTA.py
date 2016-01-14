
"""
    This class represents one FASTA file.
    It holds information:
        file path, sequence name and full sequence data
"""
class FASTA:

    """ Constructor for FASTA file, it takes file path as only argument """
    def __init__(self, file_path):
        self.file_path = file_path
        self.data = []
        self.sequence_name = ''

    """ Method used to actually read and parse file """
    def read(self):
        file = open(self.file_path, 'r')

        for line in file:
            if line.startswith('>'):
                self.sequence_name = line.split()[0][1:]        # skip '<'
            else:
                for c in line:
                    if c.isalpha():
                        self.data.append(c)

        file.close()
