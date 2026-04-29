class_name FormatWriter

static func format(variant: Variant, name: String):
	if variant is Vector2:
		return "VECTOR_2 %s %s %s" % [name, variant.x, variant.y]
	elif variant is Vector3:
		return "VECTOR_3 %s %s %s %s" % [name, variant.x, variant.y, variant.z]
	elif variant is Vector4:
		return "VECTOR_4 %s %s %s %s %s" % [name, variant.x, variant.y, variant.z, variant.w]
	elif variant is Quaternion:
		return "QUATERNION %s %s %s %s %s" % [name, variant.x, variant.y, variant.z, variant.w]
	elif variant is Mesh:
		return "MESH %s %s" % [name, variant.resource_path]
	elif variant is PackedScene:
		return "PREFAB %s %s" % [name, variant.resource_path]
	elif variant is String:
		return "STRING %s %s" % [name, variant]
	elif variant is int:
		return "INT %s %s" % [name, variant]
	elif variant is Shape3D:
		var res: String = "COLLIDER_INFO %s " % [name]
		var shapeInfo:String = ""
		if variant is BoxShape3D:
			var box:BoxShape3D = variant as BoxShape3D
			shapeInfo = "BOX_COLLIDER %s %s %s" % [box.size.x, box.size.y, box.size.z]
		elif variant is SphereShape3D:
			var sphere:SphereShape3D = variant as SphereShape3D
			shapeInfo = "SPHERE_COLLIDER %s" % [sphere.radius]
		elif variant is CapsuleShape3D:
			var capsule:CapsuleShape3D = variant as CapsuleShape3D
			shapeInfo =  "CAPSULE_COLLIDER %s %s" % [capsule.radius, capsule.height]
		elif variant is CylinderShape3D:
			var cylinder:CylinderShape3D = variant as CylinderShape3D
			shapeInfo =  "CYLINDER_COLLIDER %s %s" % [cylinder.radius, cylinder.height]
		return res + shapeInfo
	return "%s %s %s" % [ type_string(typeof(variant)).to_upper(), name, str(variant)]
