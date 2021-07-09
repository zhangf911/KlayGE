#!/usr/bin/env python
#-*- coding: ascii -*-

from __future__ import print_function
import os, sys
from Build import BuildInfo

def CopyToDst(src_name, dst_dir):
	print("Copying %s to %s..." % (src_name, dst_dir))
	import shutil
	shutil.copy2(src_name, dst_dir)

def DeployKlayGE(target_dir, build_info, compiler_arch, cfg):
	import glob

	bin_dst_dir = "%s/bin/%s_%s/" % (target_dir, build_info.target_platform, compiler_arch)
	if build_info.is_windows:
		bat_suffix = "bat"
		dll_suffix = "dll"
		exe_suffix = "exe"
	elif build_info.is_darwin:
		bat_suffix = "sh"
		dll_suffix = "dylib"
		exe_suffix = ""
	else:
		bat_suffix = "sh"
		dll_suffix = "so"
		exe_suffix = ""
	output_suffix = "_%s%d" % (build_info.compiler_name, build_info.compiler_version)
	if cfg == "Debug":
		debug_suffix = "_d"
	else:
		debug_suffix = ""
	lib_suffix = "%s%s.%s" % (output_suffix, debug_suffix, dll_suffix)

	if not os.path.exists("%s/bin" % target_dir):
		os.mkdir("%s/bin" % target_dir);
	if not os.path.exists(bin_dst_dir):
		os.mkdir(bin_dst_dir);
	if not os.path.exists("%sAudio/" % bin_dst_dir):
		os.mkdir("%sAudio/" % bin_dst_dir);
	if not os.path.exists("%sInput/" % bin_dst_dir):
		os.mkdir("%sInput/" % bin_dst_dir);
	if not os.path.exists("%sRender/" % bin_dst_dir):
		os.mkdir("%sRender/" % bin_dst_dir);
	if not os.path.exists("%sScene/" % bin_dst_dir):
		os.mkdir("%sScene/" % bin_dst_dir);
	if not os.path.exists("%sScript/" % bin_dst_dir):
		os.mkdir("%sScript/" % bin_dst_dir);
	if not os.path.exists("%sShow/" % bin_dst_dir):
		os.mkdir("%sShow/" % bin_dst_dir);

	CopyToDst("KlayGE/bin/KlayGE.cfg", "%s/bin/" % target_dir);
	
	print("Deploying 7z...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/7zxa%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/LZMA%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying DXSDK...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/d3dcompiler_47.%s" % (compiler_arch, dll_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying OpenAL...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/OpenAL%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying assimp...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/assimp%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying FreeImage...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/FreeImage%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying zlib...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/zlib%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying glloader...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/glloader%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying kfont...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/kfont%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying KlayGE...\n")
	for fname in glob.iglob("KlayGE/bin/win_%s/KlayGE_Core%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/KlayGE_DevHelper*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Audio/KlayGE_Audio*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sAudio/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Input/KlayGE_Input*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sInput/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Render/KlayGE_Render*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sRender/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Scene/KlayGE_Scene*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sScene/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Script/KlayGE_Script*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sScript/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/Show/KlayGE_Show*%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, "%sShow/" % bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/PlatformDeployer%s.%s" % (compiler_arch, debug_suffix, exe_suffix)):
		CopyToDst(fname, bin_dst_dir);
	for fname in glob.iglob("KlayGE/bin/win_%s/ToolCommon%s" % (compiler_arch, lib_suffix)):
		CopyToDst(fname, bin_dst_dir);

	print("Deploying media files...\n")

	if not os.path.exists("%s/media" % target_dir):
		os.mkdir("%s/media" % target_dir);
	if not os.path.exists("%s/media/Fonts" % target_dir):
		os.mkdir("%s/media/Fonts" % target_dir);
	if not os.path.exists("%s/media/Models" % target_dir):
		os.mkdir("%s/media/Models" % target_dir);
	if not os.path.exists("%s/media/PlatConf" % target_dir):
		os.mkdir("%s/media/PlatConf" % target_dir);
	if not os.path.exists("%s/media/PostProcessors" % target_dir):
		os.mkdir("%s/media/PostProcessors" % target_dir);
	if not os.path.exists("%s/media/RenderFX" % target_dir):
		os.mkdir("%s/media/RenderFX" % target_dir);
	if not os.path.exists("%s/media/Textures" % target_dir):
		os.mkdir("%s/media/Textures" % target_dir);
	if not os.path.exists("%s/media/Textures/2D" % target_dir):
		os.mkdir("%s/media/Textures/2D" % target_dir);
	if not os.path.exists("%s/media/Textures/3D" % target_dir):
		os.mkdir("%s/media/Textures/3D" % target_dir);
	if not os.path.exists("%s/media/Textures/Cube" % target_dir):
		os.mkdir("%s/media/Textures/Cube" % target_dir);
	if not os.path.exists("%s/media/Textures/Juda" % target_dir):
		os.mkdir("%s/media/Textures/Juda" % target_dir);

	CopyToDst("KlayGE/media/Fonts/gkai00mp.kfont", "%s/media/Fonts/" % target_dir);
	CopyToDst("KlayGE/media/Models/AmbientLightProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/CameraProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/DirectionalLightProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/IndirectLightProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/PointLightProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/SpotLightProxy.glb", "%s/media/Models/" % target_dir);
	CopyToDst("KlayGE/media/Models/TubeLightProxy.glb", "%s/media/Models/" % target_dir);
	for fname in glob.iglob("KlayGE/media/PlatConf/*.plat"):
		CopyToDst(fname, "%s/media/PlatConf" % target_dir);
	for fname in glob.iglob("KlayGE/media/PostProcessors/*.ppml"):
		CopyToDst(fname, "%s/media/PostProcessors" % target_dir);
	for fname in glob.iglob("KlayGE/media/RenderFX/*.fxml"):
		CopyToDst(fname, "%s/media/RenderFX" % target_dir);
	for fname in glob.iglob("KlayGE/media/Textures/2D/*.dds"):
		CopyToDst(fname, "%s/media/Textures/2D/" % target_dir);
	CopyToDst("KlayGE/media/Textures/3D/color_grading.dds", "%s/media/Textures/3D/" % target_dir);
	for fname in glob.iglob("KlayGE/media/Textures/Cube/Lake_CraterLake03_*.dds"):
		CopyToDst(fname, "%s/media/Textures/Cube/" % target_dir);
	for fname in glob.iglob("KlayGE/media/Textures/Cube/rnl_cross_*.dds"):
		CopyToDst(fname, "%s/media/Textures/Cube/" % target_dir);
	for fname in glob.iglob("KlayGE/media/Textures/Cube/uffizi_cross_*.dds"):
		CopyToDst(fname, "%s/media/Textures/Cube/" % target_dir);
	for fname in glob.iglob("KlayGE/media/Textures/Juda/*.jdt"):
		CopyToDst(fname, "%s/media/Textures/Juda/" % target_dir);

if __name__ == "__main__":
	if len(sys.argv) > 1:
		target_dir = sys.argv[1]
		build_info = BuildInfo.FromArgv(sys.argv, 1)
		for cfg in build_info.cfg:
			for compiler_info in build_info.compilers:
				DeployKlayGE(target_dir, build_info, compiler_info.arch, cfg)
	else:
		print("Usage: DeployKlayGE.py target_dir [project] [compiler] [arch] [config]")
