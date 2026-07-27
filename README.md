# Compression software using Deflate algorithm

The goal of this project is learning about compression as a branch of information theory (in which I've been 
intrested during the past three years) and at the same time getting more comfortable with C.

## 1. First, you need to implement lz77_compressor().

LZ77 algorithm allows us to transform repeating sequences into tokens that have reference to the first time the the sequence appeared (basically your trying to construct a bijection).