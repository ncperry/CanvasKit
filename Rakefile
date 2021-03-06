require 'open3'

@remote_name = "origin"
@current_version = ""
@new_version = ""
@podspec_name

namespace :pod do

  desc 'push the cocoapod to the public or private specs repo'
  task :submit do

    STDOUT.puts "> Is this a public cocoapod? [yes, no]"
    input = STDIN.gets.chomp
    raise "#{input} is not a valid response" unless ['yes', 'y', 'no', 'n'].include?(input)

    cmd = ''
    if input == 'yes' || input == 'y'
      cmd = "pod trunk push --verbose #{get_podspec_name}"
    else
      raise '> This is not ready for prime time. Were working on it.'
      # cmd = "pod push #{get_podspec_name}"
    end

    %x(#{cmd})

  end

  desc 'Updates the podspec with the new version, pushes changes and tags for release.'
  task :release do

    STDOUT.puts "> What kind of release are we dealing with here? [major, minor, patch]"
    input = STDIN.gets.chomp
    raise "#{input} is not a valid release type. Try again." unless ["major", "minor", "patch"].include?(input)

    @podspec_name = get_podspec_name

    current_version = current_version_for_podspec(@podspec_name)
    @current_version = current_version
    new_version = ''

    if is_valid_version_scheme(current_version)
      new_version =

      case input
      when "major"
        incremented_major_version_for_version(current_version)
      when "minor"
        incremented_minor_version_for_version(current_version)
      when "patch"
        incremented_patch_version_for_version(current_version)
      else
      end
    else
      new_version = prompt_user_for_valid_version_string
    end

    verify_changes(@new_version)

    update_podspec_for_new_version(@podspec_name, new_version)
    prompt_for_remote_name
    wrap_up
  end

  desc 'Convenience task to ensure the correct podspec is being identified'
  task :identify_podspec do
    name = get_podspec_name
    puts "Found a podspec named: #{name}"
  end

  def get_podspec_name
    files = Dir.glob("*.podspec")

    raise "Could not find a podspec" unless files.count > 0

    return files[0]
  end

  def verify_changes(new_version)

    STDOUT.puts "> The version has been updated from #{@current_version} to #{new_version}, would you like to proceed? [yes, no]"
    input = STDIN.gets.chomp
    raise "Release cancelled by user" unless input == "yes"

  end

  def prompt_for_remote_name
    STDOUT.puts "> What is the name of the remote repository we are releasing to?"
    input = STDIN.gets.chomp
    raise "You must enter a name for the remote repository" unless input.length > 0
    @remote_name = input
  end

  def wrap_up
    commit_changes
    lint_repo
    tag_repo(@new_version)
    push_tags
  end

  def commit_changes
    puts "Commiting Changes..."
    cmd = "git add -u && git commit -m 'updated podspec for new version'"
    Open3.popen3(cmd) do |stdin, stdout, stderr, wait_thr|

      puts stdout.read

      puts "Pushing changes..."
      Open3.popen3("git push #{@remote_name}") do |stdin, stdout, stderr, wait_thr|
        puts stdout.read
      end

    end
  end

  def lint_repo
    puts "Validating podspec... (this could take a while. Stay calm.)"
    cmd = "pod lib lint #{@podspec_name}"
    Open3.popen3(cmd) do |stdin, stdout, stderr, wait_thr|

      if stdout.read.include?("#{@podspec_name.split('.')[0]} passed validation")
        puts "#{@podspec_name} passed validation"

      else
        puts "There is a problem with the Podspec file: "
        puts stdout.read
      end

    end
  end

  def push_tags
    puts "Pushing tags..."
    cmd = "git push #{@remote_name} --tags"

    Open3.popen3(cmd) do |stdin, stdout, stderr, wait_thr|

      puts stdout.read

    end
  end

  def tag_repo(version)

    cmd = "git tag -a #{version} -m 'new patch'"

    Open3.popen3(cmd) do |stdin, stdout, stderr, wait_thr|

      puts stdout.read

    end

  end

  def current_version_for_podspec(file_name)

    current_version = '0.0.0'
    IO.readlines(file_name).map do |line|

      if line.include?('version ')
        current_version = /.*version\s+=\s+('|")(.*)('|")/.match(line)[2]
      end

    end

    current_version

  end

  def incremented_patch_version_for_version(version_string)
    version_string.gsub(/(\d*\.\d*\.)(\d*)/) do |match|
      @new_version = "#{Regexp.last_match[1]}#{Regexp.last_match[2].to_i.next}"
    end

    @new_version
  end

  def incremented_minor_version_for_version(version_string)
    version_string.gsub(/(\d*\.)(\d*)(\.\d*)/) do |match|
      @new_version = "#{Regexp.last_match[1]}#{Regexp.last_match[2].to_i.next}.0"
    end
    @new_version
  end

  def incremented_major_version_for_version(version_string)
    version_string.gsub(/(\d*\.)(\d*)(\.\d*)/) do |match|
      @new_version = "#{Regexp.last_match[1].to_i.next}.0.0"
    end
    @new_version
  end

  def is_valid_version_scheme(version_string)
    version_parts = version_string.split('.')
    return version_parts.count == 3
  end


  def validate_semantic_versioning(version_string)
    version_parts = version_string.split('.')
    if version_parts.count < 3

      valid_string = prompt_user_for_valid_version_string
    else
      valid_string = version_string

    end

    valid_string

  end

  def prompt_user_for_valid_version_string
    STDOUT.puts "> Your version string does not match the Semantic Versioning Specification (http://semver.org/). Please enter a version matching the pattern MAJOR.MINOR.PATCH"
    input = STDIN.gets.chomp
    raise "#{input} is not a valid version string. See http:://semver.org for details" unless input.split('.').count == 3

    return input
  end


  def update_podspec_for_new_version(file_name, new_version)

    lines = IO.readlines(file_name).map do |line|

      if line.include?('version')
        line.gsub(/.*.version\s+=\s+'(.*)'/) do |match|
          line = match.gsub("#{$1}", new_version)
        end
      end

      line

    end

    File.open(file_name, 'w') do |file|
      file.puts lines
    end


    lines = IO.readlines(file_name).map do |line|

      if line.include?('source ')
        line.gsub(/.*:tag\s+=>+\s('|")(.*)('|")\s+}/) do |match|
          line = match.gsub("#{$2}", new_version)
        end
      end
      line
    end

    File.open(file_name, 'w') do |file|
      file.puts lines
    end

  end



end
