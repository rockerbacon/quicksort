#ifndef _LAB309_ADT_STATIC_CONTAINER_H_
#define _LAB309_ADT_STATIC_CONTAINER_H_

#include "Lab309_ADT_Container.h"
#include <stdlib.h>

template<typename dataType>
class SContainer : public Container {

	protected:
		//attributes
		dataType *data;
		size_t size;

	public:

		//constructors and destructor
		SContainer (void) {
			this->data = NULL;
			this->size = 0;
		}

		SContainer (size_t size) throw (std::bad_alloc) {
			try {
				if (size != 0) {

					this->data = (dataType*)malloc(size*sizeof(dataType));
					if (this->data == NULL) {
						throw std::bad_alloc();
					}

					this->size = size;
				} else {
					this->data = NULL;
					this->size = 0;
				}
			} catch (std::invalid_argument &error) {
				throw error;
			} catch (std::bad_alloc &error) {
				throw error;
			}
		}

		SContainer (const SContainer<dataType> &container) throw (std::bad_alloc) : SContainer<dataType> (container.size) {
			size_t i;
			for (i = 0; i < container.length; i++) {
				this->data[i] = container.data[i];
			}
			this->length = container.length;
		}

		SContainer (SContainer<dataType> &&container) {
			this->data = container.data;
			container.data = NULL;
			this->length = container.length;
			this->size = container.size;
		}

		SContainer (const std::initializer_list<dataType> &list) throw (std::invalid_argument, std::bad_alloc) : SContainer<dataType> (list.size()) {
			const size_t argc = list.size();
			const dataType *args = list.begin();
			size_t i;

			for (i = 0; i < argc; i++) {
				this->data[i] = args[i];
			}
			this->length = argc;
		}

		~SContainer (void) {
			this->erase();
		}

		//getters
		inline size_t getSize (void) const {
			return this->size;
		}

		inline bool isFull (void) const {
			return this->length == this->size;
		}

		//methods
		void resize (size_t size, bool retainData) throw (std::invalid_argument, std::bad_alloc) {
			dataType *data;
			size_t i;
			try {
				if (size == 0) {
					throw std::invalid_argument("Error on SContainer<dataType>::resize(size_t size, bool retainData: size must be greater than 0");
				} else if (size == this->size) {
					return;
				}

				if (!retainData) {
					free(this->data);
				}
				data = (dataType*)malloc(size*sizeof(dataType));
				if (data == NULL) {
					throw std::bad_alloc();
				}

				if (retainData) {
					if (size < this->length) {
						this->length = size;
					}
					for (i = 0; i < this->length; i++) {
						data[i] = this->data[i];
					}
					free(this->data);
				} else {
					this->length = 0;
				}

				this->data = data;
				this->size = size;
			} catch (std::invalid_argument &error) {
				throw error;
			} catch (std::bad_alloc &error) {
				throw error;
			}
		}

		void resize (size_t size) throw (std::invalid_argument, std::bad_alloc) {
			try {
				if (this->length > size) {
					this->resize (size, false);	//possible std::invalid_argument, std::bad_alloc throw
				} else {
					this->resize (size, true);	//possible std::invalid_argument, std::bad_alloc throw
				}
			} catch (std::invalid_argument &error) {
				throw error;
			} catch (std::bad_alloc &error) {
				throw error;
			}
		}

		inline void empty (void) {
			this->length = 0;
		}

		inline void erase (void) {
			if (this->data != NULL) {
				free(this->data);
			}
			this->data = NULL;
		}

		//operators
		//relational equality operators
		virtual bool operator== (const SContainer<dataType> &container) const {
			size_t i;

			if (this->length != container.length) {
				return false;
			}
			for (i = 0; i < this->length; i++) {
				if (this->data[i] != container.data[i]) {
					return false;
				}
			}

			return true;
		}

		inline bool operator!= (const SContainer<dataType> &container) const {
			return !this->operator==(container);
		}

};

#endif
