#ifndef MESHOBJECT_HPP
#define MESHOBJECT_HPP

#include "NetgenPluginDefs.hpp"

#ifndef OCCGEOMETRY
#define OCCGEOMETRY
#endif
#include <meshing.hpp>
#include <occgeom.hpp>

#include <vtkSmartPointer.h>

namespace netgen {
NETGENPLUGIN_DLL_HEADER
extern MeshingParameters mparam;
}

class vtkPartitionedDataSet;

class MeshObject : public netgen::Mesh {
public:
	MeshObject();
	~MeshObject() = default;

public:
	void DecomposeMesh(int nProc);

	void SetPhysicalSurfaceRegionLabel(int index, const std::string& label);
	std::string GetPhysicalSurfaceRegionLabel(int index) const;
	void SetPhysicalVolumeRegionLabel(int index, const std::string& label);
	std::string GetPhysicalVolumeRegionLabel(int index) const;

	int GetSurfaceRegionsNumber() const {
		return static_cast<int>(_physicalSurfaceRegions.size());
	}

	int GetVolumeRegionsNumber() const {
		return static_cast<int>(_physicalVolumeRegions.size());
	}

	std::map<int, std::string> GetSurfaceRegions() {
		return _physicalSurfaceRegions;
	}
	std::map<int, std::string> GetVolumeRegions() {
		return _physicalVolumeRegions;
	}

	void SetProcNumber(const int procNb) { _procNumber = procNb; }
	int GetProcNumber() const { return _procNumber; }

	void SaveDecomposedVtk(const std::string& cwd = "") const;

	static vtkSmartPointer<vtkPartitionedDataSet> GenerateGhostCells(
		const vtkSmartPointer<vtkPartitionedDataSet>& dataset);

private:
	int _procNumber = 1;

	std::map<int, std::string> _physicalSurfaceRegions;
	std::map<int, std::string> _physicalVolumeRegions;
};

#endif
