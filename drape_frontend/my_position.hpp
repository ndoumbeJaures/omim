#pragma once

#include "drape_frontend/arrow3d.hpp"
#include "drape_frontend/render_node.hpp"
#include "drape_frontend/render_state.hpp"

#include "shaders/program_manager.hpp"

#include "drape/batcher.hpp"
#include "drape/texture_manager.hpp"
#include "drape/uniform_values_storage.hpp"
#include "drape/vertex_array_buffer.hpp"

#include "geometry/screenbase.hpp"

#include <vector>
#include <utility>

namespace df
{
class MyPosition
{
public:
  explicit MyPosition(ref_ptr<dp::TextureManager> mng);

  // pt - mercator point
  void SetPosition(m2::PointF const & pt);
  void SetAzimuth(float azimut);
  void SetIsValidAzimuth(bool isValid);
  void SetAccuracy(float accuracy);
  void SetRoutingMode(bool routingMode);
  void SetPositionObsolete(bool obsolete);

  void RenderAccuracy(ScreenBase const & screen, int zoomLevel,
                      ref_ptr<gpu::ProgramManager> mng,
                      dp::UniformValuesStorage const & commonUniforms);

  void RenderMyPosition(ScreenBase const & screen, int zoomLevel,
                        ref_ptr<gpu::ProgramManager> mng,
                        dp::UniformValuesStorage const & commonUniforms);

private:
  void CacheAccuracySector(ref_ptr<dp::TextureManager> mng);
  void CachePointPosition(ref_ptr<dp::TextureManager> mng);

  enum EMyPositionPart
  {
    // Don't change the order and the values.
    MyPositionAccuracy = 0,
    MyPositionPoint = 1,
  };

  void RenderPart(ref_ptr<gpu::ProgramManager> mng,
                  dp::UniformValuesStorage const & uniforms,
                  EMyPositionPart part);

  void CacheSymbol(dp::TextureManager::SymbolRegion const & symbol,
                   dp::GLState const & state, dp::Batcher & batcher,
                   EMyPositionPart part);

  m2::PointF m_position;
  float m_azimuth;
  float m_accuracy;
  bool m_showAzimuth;
  bool m_isRoutingMode;
  bool m_obsoletePosition;

  using TPart = std::pair<dp::IndicesRange, size_t>;

  std::vector<TPart> m_parts;
  std::vector<RenderNode> m_nodes;

  Arrow3d m_arrow3d;
};
}  // namespace df
