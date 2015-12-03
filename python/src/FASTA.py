
class FASTA:

    def __init__(self, file_path):
        self.file_path = file_path
        self.data = []
        self.sequence_name = ''


    # TODO this is not working for multiple sequences in FASTA file
    def read(self):
        file = open(self.file_path, 'r')

        for line in file:
            if line.startswith('>'):
                self.sequence_name = line.split()[0][1:]        # skip '<'
            else:
                for c in line:
                    # TODO remove '_'
                    if c.isalpha() or c in ['_', '$']:
                        self.data.append(c)
