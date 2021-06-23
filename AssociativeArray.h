#ifndef ASSOCIATIVEARRAY_H_INCLUDED
#define ASSOCIATIVEARRAY_H_INCLUDED

template <typename Key, typename Value>
class AssociativeArray {
public:
    virtual void add(const Key& key, const Value& value) = 0;
    virtual Value& find(const Key& key) = 0;
    virtual const Value& find(const Key& key) const = 0;
    virtual void remove(const Key& key) = 0;

    virtual ~AssociativeArray() {};
};

#endif // ASSOCIATIVEARRAY_H_INCLUDED
