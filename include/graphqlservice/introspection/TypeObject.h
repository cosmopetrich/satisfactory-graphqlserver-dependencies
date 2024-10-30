// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

#include "IntrospectionSchema.h"

namespace graphql::introspection::object {

class [[nodiscard("unnecessary construction")]] Type final
	: public service::Object
{
private:
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveKind(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveName(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveDescription(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveFields(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveInterfaces(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolvePossibleTypes(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveEnumValues(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveInputFields(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveOfType(service::ResolverParams&& params) const;
	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolveSpecifiedByURL(service::ResolverParams&& params) const;

	[[nodiscard("unnecessary call")]] service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct [[nodiscard("unnecessary construction")]] Concept
	{
		virtual ~Concept() = default;

		[[nodiscard("unnecessary call")]] virtual service::AwaitableScalar<TypeKind> getKind() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableScalar<std::optional<std::string>> getName() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableScalar<std::optional<std::string>> getDescription() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Field>>>> getFields(std::optional<bool>&& includeDeprecatedArg) const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getInterfaces() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getPossibleTypes() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<EnumValue>>>> getEnumValues(std::optional<bool>&& includeDeprecatedArg) const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<InputValue>>>> getInputFields() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableObject<std::shared_ptr<Type>> getOfType() const = 0;
		[[nodiscard("unnecessary call")]] virtual service::AwaitableScalar<std::optional<std::string>> getSpecifiedByURL() const = 0;
	};

	template <class T>
	struct [[nodiscard("unnecessary construction")]] Model final
		: Concept
	{
		explicit Model(std::shared_ptr<T> pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		[[nodiscard("unnecessary call")]] service::AwaitableScalar<TypeKind> getKind() const override
		{
			return { _pimpl->getKind() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableScalar<std::optional<std::string>> getName() const override
		{
			return { _pimpl->getName() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableScalar<std::optional<std::string>> getDescription() const override
		{
			return { _pimpl->getDescription() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Field>>>> getFields(std::optional<bool>&& includeDeprecatedArg) const override
		{
			return { _pimpl->getFields(std::move(includeDeprecatedArg)) };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getInterfaces() const override
		{
			return { _pimpl->getInterfaces() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Type>>>> getPossibleTypes() const override
		{
			return { _pimpl->getPossibleTypes() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<EnumValue>>>> getEnumValues(std::optional<bool>&& includeDeprecatedArg) const override
		{
			return { _pimpl->getEnumValues(std::move(includeDeprecatedArg)) };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::optional<std::vector<std::shared_ptr<InputValue>>>> getInputFields() const override
		{
			return { _pimpl->getInputFields() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableObject<std::shared_ptr<Type>> getOfType() const override
		{
			return { _pimpl->getOfType() };
		}

		[[nodiscard("unnecessary call")]] service::AwaitableScalar<std::optional<std::string>> getSpecifiedByURL() const override
		{
			return { _pimpl->getSpecifiedByURL() };
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	const std::unique_ptr<const Concept> _pimpl;

	[[nodiscard("unnecessary call")]] service::TypeNames getTypeNames() const noexcept;
	[[nodiscard("unnecessary call")]] service::ResolverMap getResolvers() const noexcept;

public:
	GRAPHQLSERVICE_EXPORT explicit Type(std::shared_ptr<introspection::Type> pimpl) noexcept;
	GRAPHQLSERVICE_EXPORT ~Type();
};

} // namespace graphql::introspection::object

#endif // TYPEOBJECT_H
