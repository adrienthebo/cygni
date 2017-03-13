require 'guard/compat/plugin'
require 'thread'

module ::Guard
  class CMake < Guard::Plugin
    # @todo document builddir behavior
    # @todo support cmake flags
    def initialize(options = {})
      super
      @builddir = options.fetch(:builddir, default_builddir)
      @cmake_flags = %w[-DCMAKE_TOOLCHAIN_FILE=../cmake/teensy-arm.toolchain.cmake]
    end

    def run_all
      build
    end

    def run_on_modifications(_)
      build
    end

    private

    def default_builddir
      File.join(
        File.expand_path(File.dirname(__FILE__)),
        'build')
    end

    # @todo create build directory if not present
    # @todo run CMake if it has not been run before
    def build
      #cmake
      make
    end

    def cmake
      cmd = ['echo', 'cmake', @cmake_flags, '..'].flatten.compact
      pid = Process.spawn(*cmd, chdir: @builddir)
      Process.wait(pid)
    end

    def make
      Guard::Compat::UI.notify(
        "Build started for #{@builddir.inspect}",
        title: "CMake build triggered",
        image: :pending
      )

      pid = Process.spawn("make", chdir: @builddir)
      _, status = Process.waitpid2(pid)

      if status.exitstatus == 0
        Guard::Compat::UI.notify(
          "Build completed. Exit status: #{status.exitstatus}",
          title: "CMake build complete")
      else
        Guard::Compat::UI.notify(
          "Build completed. Exit status: #{status.exitstatus}",
          title: "CMake build FAILED",
          image: :failed)
      end
    end
  end
end

module ::Guard
  class TYC < Guard::Plugin
    def self.mutex
      @_mutex ||= Mutex.new
    end

    def self.flash(path, tyc_id)
      Guard::Compat::UI.info("Acquiring lock to flash #{tyc_id}. This might take a moment.")
      mutex.synchronize do
        flash!(path, tyc_id)
      end
    end

    def self.flash!(path, tyc_id)

      Guard::Compat::UI.notify(
        "Teensy #{tyc_id} is being reflashed with #{path}",
        title: "TYC reflash triggered.")

      cmd = ['tyc', 'upload', '-B', tyc_id, path]
      pid = Process.spawn(*cmd)
      _, status = Process.waitpid2(pid)

      if status.exitstatus == 0
        Guard::Compat::UI.notify(
          "Teensy #{tyc_id} has been reflashed. Exit status: #{status.exitstatus}",
          title: "TYC reflash complete.")
      else
        Guard::Compat::UI.notify(
          "Teensy #{tyc_id} has been reflashed. Exit status: #{status.exitstatus}",
          title: "TYC reflash FAILED.",
          image: :failed)
      end
    end

    def initialize(options = {}, &block)
      super
      puts "TODO: implement target map"
      @buildmap = options.fetch(:buildmap, {})
      @builddir = options.fetch(:builddir, default_builddir)
    end

    def start
      puts "TODO: enumerate available Teensys."
    end

    def run_all
      run_on_modifications(Dir.glob('build/*.hex'))
    end

    def run_on_modifications(paths)
      paths.each do |path|
        tyc_id = @buildmap[path]
        if tyc_id
          self.class.flash(path, tyc_id)
        else
          Guard::Compat::UI.info("Device not defined for #{path}")
        end
      end
    end

    def run_on_deletions(paths)
      puts "TODO (#{__method__}): determine use"
    end

    private

    # @todo deduplicate
    def default_builddir
      File.join(
        File.expand_path(File.dirname(__FILE__)),
        'build')
    end
  end
end

guard :cmake do
  watch(%r{^lib})
  watch(%r{^exe})
  watch(%r{CMakeLists\.txt})
  watch(%r{\.(?:cpp|hpp|h)$})
end

buildmap = {
  'build/dmx-transmit.elf.hex' => '943610-Teensy',
  'build/dmx-recv.elf.hex' => '1073050-Teensy',
}

guard(:tyc, buildmap: buildmap) do
  watch(%r{^build/(.*\.hex)})
end
