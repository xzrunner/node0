#pragma once

#include "node0/NodeComp.h"

#include <string>

namespace n0
{

class CompIdentity : public NodeComp
{
public:
	CompIdentity();

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual CompID TypeID() const override {
		return GetCompTypeID<CompIdentity>();
	}
	virtual std::unique_ptr<NodeComp> Clone(const SceneNode& obj) const override;

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