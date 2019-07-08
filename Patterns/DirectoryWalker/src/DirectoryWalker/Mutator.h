#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>

template<class MutableT>
struct Mutator
{
    virtual ~Mutator() = default;
    virtual void Mutate(MutableT& _mutable) = 0;
};

template<class MutableT, class MutatorT>
struct MutatorChain : public Mutator<MutableT>
{
        void AddMutator(MutatorT* mutator)
        {
            m_mutations.push_back(mutator);
        }
        void Mutate(MutableT& _mutable) override
        {
            for (auto& mutator : m_mutations)
            {
                mutator->Mutate(_mutable);
            }
        }
    private:
        std::vector<MutatorT*> m_mutations;
};

#endif //MUTATOR_H