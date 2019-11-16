#include"RNA.h"

RNA::jab::jab(RNA* const RNA_received, size_t index_nucleotide) : jab_index(index_nucleotide), jab_RNA(RNA_received) {};	// jab Constructor
RNA::jab & RNA::jab::operator= (Nucleotide Nucleotide_add) {																// jab Operator =
	if (jab_index < jab_RNA->RNA_size) {
		//jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)] = ((jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)]) & (~((size_t)3 << (2 * (jab_index % (sizeof(size_t) * 4)))))) | (Nucleotide_add << (2 * (jab_index % (sizeof(size_t) * 4))));
		std::cout << "Error! RNA don't change in middle";
		return *this;
	}
	else {
		if (jab_RNA->RNA_size == 0) {
			RNA RNA_new(A, jab_index + 1);
			*jab_RNA = RNA_new;
			jab_RNA->RNA_arr[0] = Nucleotide_add;
			return *this;
		}
		else {
			size_t kkk = sizeof(jab_RNA->RNA_arr);
			if (kkk/sizeof(size_t) > (jab_index / (sizeof(size_t) * 4))) {
				jab_RNA->RNA_size = jab_index + 1;
				jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)] = ((jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)]) & (~((size_t)3 << (2 * (jab_index % (sizeof(size_t) * 4)))))) | (Nucleotide_add << (2 * (jab_index % (sizeof(size_t) * 4))));
				return *this;
			}
			RNA RNA_new(A, jab_index * 2);
			RNA_new.RNA_size = jab_index + 1;
			for (size_t i = 0; i < ((jab_RNA->RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
				RNA_new.RNA_arr[i] = jab_RNA->RNA_arr[i];
			}
			RNA_new.RNA_arr[(jab_RNA->RNA_size - 1) / (sizeof(size_t) * 4)] = (RNA_new.RNA_arr[(jab_RNA->RNA_size - 1) / (sizeof(size_t) * 4)] << (2 * (sizeof(size_t) * 4 - (jab_RNA->RNA_size - 1) % (sizeof(size_t) * 4) - 1))) >> (2 * (sizeof(size_t) * 4 - (jab_RNA->RNA_size - 1) % (sizeof(size_t) * 4) - 1));
			*jab_RNA = RNA_new;
			jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)] = ((jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)]) & (~((size_t)3 << (2 * (jab_index % (sizeof(size_t) * 4)))))) | (Nucleotide_add << (2 * (jab_index % (sizeof(size_t) * 4))));
			return *this;
		}
	}
}
RNA::jab::operator Nucleotide() const {																						// Nucleotide_type
	switch ((jab_RNA->RNA_arr[jab_index / (sizeof(size_t) * 4)] >> (2 * (jab_index % (sizeof(size_t) * 4)))) & 3)
	{
	case 0:
		return A;
	case 1:
		return G;
	case 2:
		return C;
	case 3:
		return T;
	}
}
RNA::RNA() : RNA_size(0), RNA_arr(nullptr) {}																				// Constructor
RNA::RNA(Nucleotide Nucl, size_t size) : RNA_size(size) {																	// Constructor
	if (RNA_size != 0) {
		RNA_arr = new size_t[(RNA_size - 1) / (sizeof(size_t) * 4) + 1];
		for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
			RNA_arr[i] = 0;
			for (size_t j = 0; j < sizeof(size_t) * 4; j++) {
				RNA_arr[i] = RNA_arr[i] | (Nucl << (2 * j));
			}
		}
	}
	else
		RNA_arr = nullptr;
}
RNA::RNA(const RNA& RNA_2) : RNA_size(RNA_2.RNA_size) {																		// Copy constructor
	if (RNA_size != 0) {
		RNA_arr = new size_t[(RNA_size - 1) / (sizeof(size_t) * 4) + 1];
		for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
			RNA_arr[i] = RNA_2.RNA_arr[i];
		}
	}
	else
		RNA_arr = nullptr;
}
RNA::~RNA() {																												// Destructor
	delete[] RNA_arr;
	RNA_arr = nullptr;
}
size_t RNA::RNA_length() const { return RNA_size; }																			// RNA_length
RNA& RNA::operator= (const RNA& RNA_2) {																					// Operator =
	if (&RNA_2 == this) return *this;
	RNA_size = RNA_2.RNA_size;
	delete[] RNA_arr;
	if (RNA_size != 0) {
		RNA_arr = new size_t[(RNA_size - 1) / (sizeof(size_t) * 4) + 1];
		for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
			RNA_arr[i] = RNA_2.RNA_arr[i];
		}
	}
	else
		RNA_arr = nullptr;
	return *this;
}
RNA::jab RNA::operator[] (size_t index) {																					// Operator []
	jab Nucl(this, index);
	return Nucl;
}
Nucleotide RNA::operator[] (size_t index) const {																			// Operator []
	RNA RNA_new(*this);
	const jab Nucl(&RNA_new, index);
	return Nucl;
}
std::ostream& operator<< (std::ostream& out, const RNA& RNA) {															// Operator <<
	if (RNA.RNA_size == 0) {
		return out;
	}
	for (size_t i = 0; i < RNA.RNA_size; i++) {
		switch ((Nucleotide)RNA[i])
		{
		case A:
			out << "A";
			break;
		case G:
			out << "G";
			break;
		case C:
			out << "C";
			break;
		case T:
			out << "T";
			break;
		default:
			break;
		}
	}
	return out;
}
RNA RNA::operator! () const {																								// Operator !
	RNA RNA_new(*this);
	if (RNA_size != 0) {
		for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
			RNA_new.RNA_arr[i] = ~RNA_new.RNA_arr[i];
		}
	}
	return RNA_new;
}
bool RNA::operator== (const RNA& RNA_2) const {																				// Operator ==
	if (RNA_size == RNA_2.RNA_size) {
		if (RNA_size != 0) {
			bool answer = 1;
			for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
				if (RNA_arr[i] != RNA_2.RNA_arr[i]) {
					answer = 0;
					break;
				}
			}
			return answer;
		}
		else
			return 1;
	}
	else
		return 0;
}
bool RNA::operator!= (const RNA& RNA_2) const {																				// Operator !=
	if (RNA_size == RNA_2.RNA_size) {
		if (RNA_size != 0) {
			bool answer = 0;
			for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4) + 1); i++) {
				if (RNA_arr[i] != RNA_2.RNA_arr[i]) {
					answer = 1;
					break;
				}
			}
			return answer;
		}
		else
			return 0;
	}
	else
		return 1;
}
bool RNA::RNA_complementarity(const RNA& RNA_2) const {																		// RNA_complementarity
	if (*this == !RNA_2) {
		return 1;
	}
	else
		return 0;
}
size_t RNA::RNA_cardinality(Nucleotide Nucl) const {																		// RNA_cardinality
	if (RNA_size != 0) {
		size_t register_nucl = 0;
		for (size_t i = 0; i < RNA_size; i++) {
			if (this->operator[](i) == Nucl) register_nucl++;
		}
		return register_nucl;
	}
	else
		return 0;
}
size_t RNA::RNA_capacity() const {
	if (RNA_size == 0) return 0;
	size_t cap = ((RNA_size - 1) / (sizeof(size_t) * 4) + 1);
	return cap;
}
RNA RNA::operator+ (const RNA& RNA_2) const {																				// Operator +
	if (RNA_size == 0) {
		RNA RNA_new(RNA_2);
		return RNA_new;
	}
	if (RNA_2.RNA_size == 0) {
		RNA RNA_new(*this);
		return RNA_new;
	}
	RNA RNA_new(A, RNA_size + RNA_2.RNA_size);
	if (RNA_new.RNA_size != 0) {
		size_t i = 0;
		for (; i < (RNA_size - 1) / (sizeof(size_t) * 4) + 1; i++) {
			RNA_new.RNA_arr[i] = RNA_arr[i];
		}
		i = i - 1;
		for (; i < (RNA_size + RNA_2.RNA_size - 1) / (sizeof(size_t) * 4); i++) {
			RNA_new.RNA_arr[i] = RNA_new.RNA_arr[i] | (RNA_2.RNA_arr[i - (RNA_size - 1) / (sizeof(size_t) * 4)] << (2 * (RNA_size % (sizeof(size_t) * 4))));
			RNA_new.RNA_arr[i + 1] = RNA_new.RNA_arr[i + 1] | (RNA_2.RNA_arr[i - (RNA_size - 1) / (sizeof(size_t) * 4)] >> (2 * ((sizeof(size_t) * 4) - RNA_size % (sizeof(size_t) * 4))));
		}
		RNA_new.RNA_arr[i] = RNA_new.RNA_arr[i] | (RNA_2.RNA_arr[i - (RNA_size - 1) / (sizeof(size_t) * 4)] << (2 * (RNA_size % (sizeof(size_t) * 4))));
	}
	return RNA_new;
}
void RNA::RNA_trim(size_t last_index) {																						// RNA_trim
	if (last_index < RNA_size) {
		RNA_size = last_index;
		if (RNA_size != 0) {
			RNA RNA_new(*this);
			delete[] RNA_arr;
			RNA_arr = new size_t[(RNA_size - 1) / (sizeof(size_t) * 4) + 1];
			for (size_t i = 0; i < ((RNA_size - 1) / (sizeof(size_t) * 4)) + 1; i++) {
				RNA_arr[i] = RNA_new.RNA_arr[i];
			}
			if (last_index % (sizeof(size_t) * 4) != 0) {
				RNA_arr[(RNA_size - 1) / (sizeof(size_t) * 4)] = ((RNA_arr[(RNA_size - 1) / (sizeof(size_t) * 4)] << (2 * ((sizeof(size_t) * 4) - (last_index % (sizeof(size_t) * 4))))) >> (2 * ((sizeof(size_t) * 4) - (last_index % (sizeof(size_t) * 4)))));
			}
		}
		else
			RNA_arr = nullptr;
	}
}
RNA RNA::RNA_split(size_t last_index) const {																				// RNA_split
	if (last_index < RNA_size) {
		RNA RNA_new;
		RNA_new.RNA_size = RNA_size - last_index;
		RNA_new.RNA_arr = new size_t[(RNA_size - 1) / (sizeof(size_t) * 4) + 1];
		if (last_index % (sizeof(size_t) * 4) != 0) {
			for (size_t i = 0; i < (RNA_new.RNA_size - 1) / (sizeof(size_t) * 4) + 1; i++) {
				RNA_new.RNA_arr[i] = (RNA_arr[last_index / (sizeof(size_t) * 4) + i] >> (2 * (last_index % (sizeof(size_t) * 4)))) | (RNA_arr[last_index / (sizeof(size_t) * 4) + i + 1] << (2 * ((sizeof(size_t) * 4) - last_index % (sizeof(size_t) * 4))));
			}
		}
		else {
			for (size_t i = 0; i < (RNA_new.RNA_size - 1) / (sizeof(size_t) * 4) + 1; i++) {
				RNA_new.RNA_arr[i] = RNA_arr[last_index / (sizeof(size_t) * 4) + i];
			}
		}
		return RNA_new;
	}
	else {
		RNA RNA_0;
		return RNA_0;
	}
}
std::unordered_map < Nucleotide, size_t, std::hash<size_t> > RNA::RNA_cardinality() const {									// undored_map
	std::unordered_map < Nucleotide, size_t, std::hash<size_t> > return_map;
	for (size_t i = 0; i < RNA_size; i++) {
		switch (this->operator[](i))
		{
		case A:
			return_map[A]++;
			break;
		case C:
			return_map[C]++;
			break;
		case G:
			return_map[G]++;
			break;
		case T:
			return_map[T]++;
			break;
		default:
			break;
		}
	}
	return return_map;
}
