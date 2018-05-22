#pragma once

#include "node0/NodeUniqueComp.h"

#include <string>

namespace n0
{

class CompIdentity : public NodeUniqueComp
{
public:
	CompIdentity();

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual UniqueCompID TypeID() const override {
		return GetUniqueCompTypeID<CompIdentity>();
	}
	virtual std::unique_ptr<NodeUniqueComp> Clone(const SceneNode& obj) const override;

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

	const std::string& GetName() const { return m_name; }
	void SetName(const std::string& name) { m_name = name; }

	uint32_t GetID() const { return m_id; }
	void SetID(uint32_t id) { m_id = id; }

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;
	std::string m_name;

	uint32_t m_id;

}; // CompIdentity

}