# Shuffling Against SCA

This repository provides the implementations, attack code, and experimental results associated with the following paper:

> **Make Shuffling Great Again: A Side-Channel Resistant Fisher-Yates Algorithm for Protecting Neural Networks**  
> Leonard Puškáč, Marek Benovič, Jakub Breier, and Xiaolu Hou, IEEE Transactions on Very Large Scale Integration (VLSI) Systems, to appear.

## Citation

If you use this repository, please cite the paper using the following BibTeX entry:

```bibtex
@ARTICLE{10988891,
author={Puskac, Leonard and Benovic, Marek and Breier, Jakub and Hou, Xiaolu},
journal={ IEEE Transactions on Very Large Scale Integration (VLSI) Systems },
title={{ Make Shuffling Great Again: A Side-Channel-Resistant Fisher–Yates Algorithm for Protecting Neural Networks }},
year={5555},
volume={},
number={01},
ISSN={1557-9999},
pages={1-13},
url = {https://doi.ieeecomputersociety.org/10.1109/TVLSI.2025.3564357},
publisher={IEEE Computer Society},
address={Los Alamitos, CA, USA},
month=may}
```

## Repository Structure

- **`capture_traces/`**  
  Contains the network implementation and the code used for trace collection.

- **`main_result/`**  
  - **`unprotected/`**: Stores traces for the unprotected implementations.  
  - **`protected/`**: Stores traces for the protected implementations.
  - **`correlations/`**: Contains attack results for the unprotected implementations.  
  - **`correlations-protected/`**: Contains attack results for the protected implementations.  
  - Example files:  
    - **`unprotected-trace.txt`**: A sample trace for the unprotected implementation.  
    - **`protected-trace.txt`**: A sample trace for the protected implementation.  

- **`cpa_vs_traces/`**  
  Includes the results for Section IV-D of the paper
- **`more_experiments/`**  
  Includes the results for appendix of the paper
