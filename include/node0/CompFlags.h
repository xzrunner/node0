#pragma once

#include "node0/NodeComp.h"

namespace n0
{

class CompFlags : public NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual CompID TypeID() const override {
		return GetCompTypeID<CompFlags>();
	}
	virtual std::unique_ptr<NodeComp> Clone(const SceneNode& obj) const override;

	template <typename T>
	bool GetFlag() const;
	template <typename T>
	void SetFlag(bool flag) const;

	void SetFlags(uint32_t flags_bitset) { m_flags_bitset = flags_bitset; }
	uint32_t GetFlags() const { return m_flags_bitset; }

	static const char* const TYPE_NAME;

private:
	mutable uint32_t m_flags_bitset;

	static const size_t MAX_FLAGS = 32;

}; // CompFlags

}

#include "node0/CompFlags.inl"