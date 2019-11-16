#pragma once
#include<iostream>
#include<unordered_map>
enum Nucleotide {																											// Nucleotide
	A = 0,
	G = 1,
	C = 2,
	T = 3
};

class RNA {																													// Class RNA
	friend class jab;
	class jab {																												// Class jab
	private:
		size_t jab_index;
		RNA* jab_RNA;
	public:
		jab(RNA* RNA_received, size_t index_nucleotide); 																	// jab Constructor
		jab& operator= (Nucleotide Nucleotide_add);																			// jab Operator =
		operator Nucleotide() const;																						// Nucleotide_type
	};
private:
	size_t RNA_size;
	size_t* RNA_arr;
public:
	RNA();																													// Constructor
	RNA(Nucleotide Nucl, size_t size);																						// Constructor
	RNA(const RNA& RNA_2);																									// Copy constructor
	~RNA();																													// Destructor
	size_t RNA_length() const;																								// RNA_length
	RNA& operator= (const RNA& RNA_2);																						// Operator =
	jab operator[] (size_t index);																							// Operator []
	Nucleotide operator[] (size_t index) const;																				// Operator []
	friend std::ostream& operator<< (std::ostream& out, const RNA& RNA);													// Operator <<
	RNA operator! () const;																									// Operator !
	bool operator== (const RNA& RNA_2) const;																				// Operator ==
	bool operator!= (const RNA& RNA_2) const;																				// Operator !=
	bool RNA_complementarity(const RNA& RNA_2) const;																		// RNA_complementarity
	size_t RNA_cardinality(Nucleotide Nucl) const;																			// RNA_cardinality
	size_t RNA_capacity() const;																							// RNA_capasity 
	RNA operator+ (const RNA& RNA_2) const;																					// Operator +
	void RNA_trim(size_t last_index);																						// RNA_trim
	RNA RNA_split(size_t last_index) const;																					// RNA_split
	std::unordered_map < Nucleotide, size_t, std::hash<size_t> > RNA_cardinality() const;									// unordered_map
};
