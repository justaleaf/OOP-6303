#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

     list_iterator& operator = (const list_iterator& other)
    {
      if (this != &other)
          m_node = other.m_node;
       return *this;
    }

    bool operator == (const list_iterator& other) const
    {
      return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
      return m_node != other.m_node;
    }

    reference operator * ()
    {
      return m_node->value;
    }

    pointer operator -> ()
    {
      return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
      if (m_node)
          m_node = m_node->next;
      return *this;
    }

    list_iterator operator ++ (int)
    {
      if (m_node)
          m_node = m_node->next;
      return *this;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
      clear();
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }
      
    list(const list& other)
    {
      m_head = m_tail = nullptr;
      *this = other;
    }

    list(list&& other): m_head(other.m_head),
                        m_tail(other.m_tail)
    {
      other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other)
    {
      if (this != &other){
          clear();
          if (other.size()){
              node <Type>* tmp = other.m_head;
              while (tmp){
                  push_back(tmp->value);
                  tmp = tmp->next;
              }
          }
      }
      return *this;
    }

    void push_back(const value_type& value)
    {
      if (!empty()){
          m_tail->next = new node <Type>(value, nullptr, m_tail);
          m_tail = m_tail->next;
      }
      else {
          m_tail = new node <Type> (value, nullptr, nullptr);
          m_head = m_tail;
      }
    }
        
    void pop_front()
    {
      if (!empty()){
          if (m_head == m_tail){
              delete m_head;
              m_head = m_tail = nullptr;
          }
          else {
              m_head = m_head->next;
              delete m_head->prev;
              m_head->prev = nullptr;
          }
      }
    }

    void pop_back()
    {
      if (!empty()){
          if (m_head == m_tail){
              delete m_head;
              m_head = m_tail = nullptr;
          }
          else {
              m_tail = m_tail->prev;
              delete m_tail->next;
              m_tail->next = nullptr;
          }
      }
    }    

    iterator insert(iterator pos, const Type& value)
    {
      node <value_type>* new_node = new node <value_type>(value,pos.m_node,pos.m_node->prev);
      if (begin() == pos)
          m_head = new_node;
      else
          pos.m_node->prev->next = new_node;
      pos.m_node->prev = new_node;
      pos.m_node = new_node;
      return pos;
    }

    iterator erase(iterator pos)
    {
          if (pos == begin()){
              pop_front();
              return m_head;
          }
          else if (pos.m_node == m_tail){
              pop_back();
              return m_tail;
          }
          node<value_type> *tmp = pos.m_node;
          iterator ret (tmp->next);
          tmp->prev->next = tmp->next;
          tmp->next->prev = tmp->prev;
          delete tmp;
          return ret;
          
    }

    reference front()
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail->value;
    }
        
    void clear()
    {
      while (m_head){
          if (m_head->next){
              m_head = m_head->next;
              delete m_head->prev;
          }
          else {
              delete m_head;
              m_head = m_tail = nullptr;
          }
      }
    }

    bool empty() const
    {
      return (m_head == nullptr);
    }

    size_t size() const
    {
      size_t m_size = 0;
      node <Type> * tmp = m_head;
      while (tmp){
          m_size++;
          tmp = tmp->next;
      }
      return m_size;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
