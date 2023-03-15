import torch

if torch.cuda.is_available():
    print('Use Cuda')
else:
    print('No Cuda')