// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CesiumGltf/PropertyType.h"
#include "UObject/ObjectMacros.h"
#include "CesiumMetadataValueType.generated.h"

/**
 * The Blueprint type that can losslessly represent values of a given property.
 */
UENUM(BlueprintType)
enum class ECesiumMetadataBlueprintType : uint8 {
  /* Indicates a value cannot be represented in Blueprints. */
  None,
  /* Indicates a value is best represented as a Boolean. */
  Boolean,
  /* Indicates a value is best represented as a Byte (8-bit unsigned integer).
   */
  Byte,
  /* Indicates a value is best represented as a Integer (32-bit signed). */
  Integer,
  /* Indicates a value is best represented as a Integer64 (64-bit signed). */
  Integer64,
  /* Indicates a value is best represented as a Float (32-bit). */
  Float,
  /* Indicates a value is best represented as a Float64 (64-bit). */
  Float64,
  /* Indicates a value is best represented as a FVector2D (2-dimensional
     integer vector). */
  FIntPoint,
  /* Indicates a value is best represented as a FVector2D (2-dimensional
     double-precision vector). */
  FVector2D,
  /* Indicates a value is best represented as a FIntVector (3-dimensional
     integer vector). */
  FIntVector,
  /* Indicates a value is best represented as a FVector3f (3-dimensional
     single-precision vector). */
  FVector3f,
  /* Indicates a value is best represented as a FVector3 (3-dimensional
     double-precision vector). */
  FVector3,
  /* Indicates a value is best represented as a FVector4 (4-dimensional
     double-precision vector). */
  FVector4,
  /* Indicates a value is best represented as a FMatrix (4-by-4 double-precision
     matrix). */
  FMatrix,
  /* Indicates a value is best represented as a FString. This can be used as a
     fallback for types with no proper Blueprints representation. */
  String,
  /* Indicates a value is best represented as a CesiumMetadataArray. */
  Array
};

// True types are cast, reintepreted, or parsed before being packed into gpu
// types when encoding into a texture.
enum class ECesiumMetadataPackedGpuType : uint8 { None, Uint8, Float };

// UE requires us to have an enum with the value 0.
// Invalid / None should have that value, but just make sure.
static_assert(int(CesiumGltf::PropertyType::Invalid) == 0);
static_assert(int(CesiumGltf::PropertyComponentType::None) == 0);

/**
 * The type of a metadata property in EXT_feature_metadata. This has been
 * deprecated; use FCesiumMetadataValueType to get the complete type information
 * of a metadata property instead.
 */
UENUM(BlueprintType)
enum class ECesiumMetadataTrueType_DEPRECATED : uint8 {
  None_DEPRECATED = 0,
  Int8_DEPRECATED,
  Uint8_DEPRECATED,
  Int16_DEPRECATED,
  Uint16_DEPRECATED,
  Int32_DEPRECATED,
  Uint32_DEPRECATED,
  Int64_DEPRECATED,
  Uint64_DEPRECATED,
  Float32_DEPRECATED,
  Float64_DEPRECATED,
  Boolean_DEPRECATED,
  Enum_DEPRECATED,
  String_DEPRECATED,
  Array_DEPRECATED
};

/**
 * The type of a metadata property in EXT_structural_metadata.
 */
UENUM(BlueprintType)
enum class ECesiumMetadataType : uint8 {
  Invalid = 0,
  Scalar = int(CesiumGltf::PropertyType::Scalar),
  Vec2 = int(CesiumGltf::PropertyType::Vec2),
  Vec3 = int(CesiumGltf::PropertyType::Vec3),
  Vec4 = int(CesiumGltf::PropertyType::Vec4),
  Mat2 = int(CesiumGltf::PropertyType::Mat2),
  Mat3 = int(CesiumGltf::PropertyType::Mat3),
  Mat4 = int(CesiumGltf::PropertyType::Mat4),
  Boolean = int(CesiumGltf::PropertyType::Boolean),
  Enum = int(CesiumGltf::PropertyType::Enum),
  String = int(CesiumGltf::PropertyType::String),
};

/**
 * The component type of a metadata property in EXT_structural_metadata. Only
 * applicable if the property has a Scalar, VecN, or MatN type.
 */
UENUM(BlueprintType)
enum class ECesiumMetadataComponentType : uint8 {
  None = 0,
  Int8 = int(CesiumGltf::PropertyComponentType::Int8),
  Uint8 = int(CesiumGltf::PropertyComponentType::Uint8),
  Int16 = int(CesiumGltf::PropertyComponentType::Int16),
  Uint16 = int(CesiumGltf::PropertyComponentType::Uint16),
  Int32 = int(CesiumGltf::PropertyComponentType::Int32),
  Uint32 = int(CesiumGltf::PropertyComponentType::Uint32),
  Int64 = int(CesiumGltf::PropertyComponentType::Int64),
  Uint64 = int(CesiumGltf::PropertyComponentType::Uint64),
  Float32 = int(CesiumGltf::PropertyComponentType::Float32),
  Float64 = int(CesiumGltf::PropertyComponentType::Float64),
};

/**
 * Represents the true value type of a metadata property or value, according to
 * how the property is defined in EXT_structural_metadata.
 */
USTRUCT(BlueprintType)
struct CESIUMRUNTIME_API FCesiumMetadataValueType {
  GENERATED_USTRUCT_BODY()

  FCesiumMetadataValueType()
      : Type(ECesiumMetadataType::Invalid),
        ComponentType(ECesiumMetadataComponentType::None),
        bIsArray(false) {}

  FCesiumMetadataValueType(
      ECesiumMetadataType InType,
      ECesiumMetadataComponentType InComponentType,
      bool IsArray)
      : Type(InType), ComponentType(InComponentType), bIsArray(IsArray) {}

  /**
   * The type of the metadata property or value.
   */
  UPROPERTY(BlueprintReadWrite, Category = "Cesium")
  ECesiumMetadataType Type;

  /**
   * The component of the metadata property or value. Only applies when the type
   * is a Scalar, VecN, or MatN type.
   */
  UPROPERTY(BlueprintReadWrite, Category = "Cesium")
  ECesiumMetadataComponentType ComponentType;

  /**
   * Whether or not this represents an array containing elements of the
   * specified types.
   */
  UPROPERTY(BlueprintReadWrite, Category = "Cesium")
  bool bIsArray;

  inline bool operator==(const FCesiumMetadataValueType& ValueType) {
    return Type == ValueType.Type && ComponentType == ValueType.ComponentType &&
           bIsArray == ValueType.bIsArray;
  }
};
