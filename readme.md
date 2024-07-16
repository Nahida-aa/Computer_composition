# Computer_composition

```mermaid
graph BT
    A[transistors] --> B(Circuit Design)
    B --> C(Digital Design)
    C --> D(DataPath & Control Unit)
    D --> E[Processor]
    D --> F[Memory]
    D --> G[IO system]
    E --> H["Instruction Set Architecture(ISA)"]
    F --> H
    G --> H
    H --> I[Assembler]
    H --> J[Compiler & Interpreter]
    H --> K[Operation System]
    I --> J
    I --> K
    J --> K
    K --> L[Application]
    H --> L
    J --> L
    I --> L
```

- Hardware and software interface
  - [C](C/README.md)
  - Assembly
- CPU
  - RISC-V
- schematics
  - Verilog or VHDl
  - logisim or Digital

## [C](C/README.md)

### 1.Intro,Pointers-Number Rep Review & Overview an

### 2.Arrays,Strings,More Pointers

### 3.C Memory

## [Labs](Labs/README.md)

Great Idea

### 1.Abstraction(Levels of Representation/Interpretation)

### 2.moore's law(摩尔定律)

### 3.Principle of Locality

#### Memory Hierarchy

```mermaid
flowchart TB
    subgraph a[Virtual Memory\Mechanical Hard Disk]
    a1["File-Based Memory"]
    end

    subgraph b[Solid State Memory\SSD,USB Flash Memory]
    b1[NoN-Volatile File-Based Memory]
    end

    subgraph c[Physical Memory\EDO,SD-RAM,DDR-SDRAM,RD-RAM...]
    c1["Random Access Memory(RAM)"]
    end

    subgraph d2[CPU]
    d21[Processor Register]
    end

    subgraph d1[CPU Cache]
    d11[Level 1 Cache] --> d12
    d12[Level 2 Cache] --> d13
    d13[Level 3 Cache]
    end

    d2 --> d1
    d2 --> d11
    d1 --> c
    d13 --> c
    c --> b
    b --> a
```

### 4.Parallelism

### 5.Dependability via Redundancy
