#pragma once

#include <iostream>

using namespace std;

template<class T>
class TNode
{
protected:
    TNode<T>* next;
    TNode<T>* prev;
    T* data;
public:
    TNode() : next(nullptr), prev(nullptr), data(nullptr) {}

    ~TNode() {
        next = prev = nullptr;
        data = nullptr;
    }

    TNode(TNode<T>* n, TNode<T>* p, T* d) : next(n), prev(p), data(d) {}

    TNode(const TNode<T>& p) : next(p.next), prev(p.prev), data(new T(*(p.data))) {}

    TNode(TNode<T>&& p) noexcept : next(p.next), prev(p.prev), data(p.data) 
    {
        p.next = p.prev = nullptr;
        p.data = nullptr;
    }

    TNode<T>& operator=(const TNode<T>& p) 
    {
        if (this != &p) 
        {
            next = p.next;
            prev = p.prev;
            delete data;
            data = new T(*(p.data));
        }
        return *this;
    }

    TNode<T>& operator=(TNode<T>&& p) noexcept 
    {
        if (this != &p) 
        {
            next = p.next;
            prev = p.prev;
            delete data;
            data = p.data;
            p.next = p.prev = nullptr;
            p.data = nullptr;
        }
        return *this;
    }

    TNode<T>* GetNext() 
    {
        return next;
    }

    TNode<T>* GetPrev()
    {
        return prev;
    }

    T* GetData() 
    {
        return data;
    }

    void SetNext(TNode<T>* n) 
    {
        next = n;
    }

    void SetPrev(TNode<T>* p) 
    {
        prev = p;
    }

    void SetData(T* d) 
    {
        data = d;
    }
    template <class U>
    friend class TList;
};

template<class T>
class TListIterator;

template<class T>
class TList
{
protected:
    TNode<T>* begin_;
    TNode<T>* end_;
    int count;
public:
    TList() : begin_(nullptr), end_(nullptr), count(0) {}

    ~TList() 
    {
        TNode<T>* tmp2 = begin_;
        while (tmp2 != nullptr)
        {
            tmp2 = tmp2->next;
            delete begin_;
            begin_ = tmp2;
        }
        begin_ = nullptr;
        end_ = nullptr;
        count = 0;
    }

    TList(const TList<T>& p)
    {
        TNode<T>* tmp = p.begin_;
        begin_ = new TNode<T>(nullptr, nullptr, p.begin_->data);
        TNode<T>* tmp2 = begin_;

        while (tmp->next != nullptr)
        {
            TNode<T>* a = new TNode<T>(nullptr, tmp2, tmp->next->data);
            tmp2->next = a;
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
        end_ = tmp2;
        count = p.count;
    }

    TList(TList<T>&& p) noexcept
    {
        TNode<T>* tmp = p.begin_;
        begin_ = new TNode<T>(nullptr, nullptr, p.begin_->data);
        TNode<T>* tmp2 = begin_;

        while (tmp->next != nullptr)
        {
            TNode<T>* a = new TNode<T>(nullptr, tmp2, tmp->next->data);
            tmp2->next = a;
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
        end_ = tmp2;
        count = p.count;
        tmp = p.begin_;
        while (tmp!=nullptr)
        {
            tmp = tmp->GetNext();
            delete tmp->GetPrev();
        }
        p.count = 0;
    }

    TList<T>& operator=(TList<T>&& p) noexcept 
    {
        if (this != &p) {
            TNode<T>* tmp = p.begin_;
            begin_ = new TNode<T>(nullptr, nullptr, p.begin_->data);
            TNode<T>* tmp2 = begin_;

            while (tmp->next != nullptr)
            {
                TNode<T>* a = new TNode<T>(nullptr, tmp2, tmp->next->data);
                tmp2->next = a;
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            end_ = tmp2;
            count = p.count;
            tmp = p.begin_;
            while (tmp != nullptr)
            {
                tmp = tmp->GetNext();
                delete tmp->GetPrev();
            }
            p.count = 0;
        }
        return *this;
    }

    TList<T>& operator=(const TList<T>& p) 
    {
        if (this != &p) 
        {
            TNode<T>* tmp = p.begin_;
            begin_ = new TNode<T>(nullptr, nullptr, p.begin_->data);
            TNode<T>* tmp2 = begin_;

            while (tmp->next != nullptr)
            {
                TNode<T>* a = new TNode<T>(nullptr, tmp2, tmp->next->data);
                tmp2->next = a;
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            end_ = tmp2;
            count = p.count;
        }
        return *this;
    }

    void PushBegin(T* a) 
    {
        TNode<T>* newNode = new TNode<T>(begin_, nullptr, a);
        if (begin_ != nullptr)
            begin_->SetPrev(newNode);
        else
            end_ = newNode;
        begin_ = newNode;
        count++;
    }

    void PushEnd(T* a) 
    {
        TNode<T>* newNode = new TNode<T>(nullptr, end_, a);
        if (end_ != nullptr)
            end_->SetNext(newNode);
        else
            begin_ = newNode;
        end_ = newNode;
        count++;
    }

    void DelBegin() 
    {
        if (begin_ != nullptr) 
        {
            TNode<T>* temp = begin_;
            begin_ = begin_->GetNext();
            if (begin_ != nullptr)
                begin_->SetPrev(nullptr);
            else
                end_ = nullptr;
            delete temp;
            count--;
        }
    }

    void DelEnd() 
    {
        if (end_ != nullptr) 
        {
            TNode<T>* temp = end_;
            end_ = end_->GetPrev();
            if (end_ != nullptr)
                end_->SetNext(nullptr);
            else
                begin_ = nullptr;
            delete temp;
            count--;
        }
    }
    template <class U>
    friend class TListIterator;

    TListIterator<T> begin() 
    {
        return TListIterator<T>(*this, *begin_);
    }

    TListIterator<T> end()
    {
        return TListIterator<T>(*this, *end_->GetNext());
    }

    int GetLength() {
        return count;
    }
};

template<class T>
class TListIterator
{
protected:
    TNode<T>* curr;
    TList<T>& list;
public:
    TListIterator(TList<T>& l, TNode<T>& p) : list(l), curr(&p) {}

    TListIterator(const TListIterator<T>& p) : list(p.list), curr(p.curr) {}

    TListIterator(TListIterator<T>&& p) noexcept : list(p.list), curr(p.curr) 
    {
        p.curr = nullptr;
    }

    ~TListIterator() 
    {
        curr = nullptr;
    }

    /*void PushAfter(T* a) 
    {
        if (curr != nullptr) 
        {
            TNode<T>* newNode = new TNode<T>(curr->GetNext(), curr, a);
            if (curr->GetNext() != nullptr)
                curr->GetNext()->SetPrev(newNode);
            else
                list.GetEnd().curr = newNode;
            curr->SetNext(newNode);
            list.count++;
        }
    }

    void PushBefore(T* a) 
    {
        if (curr != nullptr) 
        {
            TNode<T>* newNode = new TNode<T>(curr, curr->GetPrev(), a);
            if (curr->GetPrev() != nullptr)
                curr->GetPrev()->SetNext(newNode);
            else
                list.GetBegin().curr = newNode;
            curr->SetPrev(newNode);
            list.count++;
        }
    }*/

    T* operator*() 
    {
        return curr->GetData();
    }

    TListIterator<T>& operator= (const TListIterator<T>& p) 
    {
        if (this != &p) 
        {
            list = p.list;
            curr = p.curr;
        }
        return *this;
    }

    TListIterator<T>& operator= (TListIterator<T>&& p) noexcept 
    {
        if (this != &p) 
        {
            list = p.list;
            curr = p.curr;
            p.curr = nullptr;
        }
        return *this;
    }
    TListIterator<T>& operator++() 
    {
        curr = curr->GetNext();
        return *this;
    }

    TListIterator<T>& operator--() 
    {
        curr = curr->GetPrev();
        return *this;
    }

    bool operator== (const TListIterator<T>& p) 
    {
        return curr == p.curr;
    }

    bool operator!= (const TListIterator<T>& p) 
    {
        return curr != p.curr;
    }

    /* void Delete() 
    {
        if (curr != nullptr) 
        {
            if (curr->GetPrev() != nullptr)
                curr->GetPrev()->SetNext(curr->GetNext());
            else
                list.GetBegin().curr = curr->GetNext();

            if (curr->GetNext() != nullptr)
                curr->GetNext()->SetPrev(curr->GetPrev());
            else
                list.GetEnd().curr = curr->GetPrev();

            curr = nullptr;
            list.count--;
        }
    }*/

};