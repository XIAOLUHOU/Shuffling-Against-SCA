# Shuffling Against SCA

This repository provides the implementations, attack code, and experimental results associated with the following paper:

> **Make Shuffling Great Again: A Side-Channel Resistant Fisher-Yates Algorithm for Protecting Neural Networks**  
> Leonard Puškáč, Marek Benovič, Jakub Breier, and Xiaolu Hou, IEEE Transactions on Very Large Scale Integration (VLSI) Systems, to appear.

## Citation

If you use this repository, please cite the paper using the following BibTeX entry:

```bibtex
@inproceedings{puskac2024make,
  title     = {Make Shuffling Great Again: A Side-Channel Resistant Fisher-Yates Algorithm for Protecting Neural Networks},
  author    = {Leonard Puškáč and Marek Benovič and Jakub Breier and Xiaolu Hou}
}
```

## Repository Structure

- **`capture_traces/`**  
  Contains the network implementation and the code used for trace collection.

- **Trace Data**  
  - **`unprotected/`**: Stores traces for the unprotected implementations.  
  - **`protected/`**: Stores traces for the protected implementations.  
  - Example files:  
    - **`unprotected-trace.txt`**: A sample trace for the unprotected implementation.  
    - **`protected-trace.txt`**: A sample trace for the protected implementation.  

- **`CPA_attack/`**  
  Includes the Jupyter Notebook file implementing the CPA attack.

- **Attack Results**  
  - **`correlations/`**: Contains attack results for the unprotected implementations.  
  - **`correlations-protected/`**: Contains attack results for the protected implementations.  

- **`shuffling_analysis/`**  
  Contains analysis code for evaluating the computational overhead of the proposed shuffling countermeasure.


